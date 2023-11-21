#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

int valor = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Nome do dispositivo Bluetooth
}

void loop() {
  // Construir o JSON
  String json = "{\"valor\": " + String(valor) + "}";
  
  // Enviar o JSON via Bluetooth
  SerialBT.println(json);
  
  // Incrementar o valor a cada segundo
  valor++;
  delay(1000);
}