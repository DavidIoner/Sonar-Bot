#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = "RoboSonar";
const char *password = "SuaSenha";

ESP8266WebServer server(80);

void handleRoot() {
    // Criar um objeto JSON
    DynamicJsonDocument doc(1024);
    doc["sensor1"] = 1;
    doc["sensor2"] = 2;
    // Adicionar mais campos conforme necessário...

    // Serializar o JSON para uma String
    String jsonString;
    serializeJson(doc, jsonString);

    // Enviar o JSON pela conexão Wi-Fi
    server.send(200, "application/json", jsonString);
}

void setup() {
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    
    // Definir a função de tratamento para a rota "/"
    server.on("/", HTTP_GET, handleRoot);

    // Iniciar o servidor
    server.begin();

    // Resto do seu código de inicialização...
}

void loop() {
    // Lidar com solicitações do servidor
    server.handleClient();

    // Seu código de loop...
}