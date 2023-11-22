#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);  
  SerialBT.begin("ESP32_BT_MASTER", true); // Nome do dispositivo Bluetooth e definição como mestre
  bool connected = SerialBT.connect("ESP32_BT"); // Dispositivo escravo a se conectar
  if(connected) {
    Serial.println("Conexão bem sucedida!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Falha ao conectar! 10 segundos sem resposta");
    }
  }
}

void loop() {
  if (SerialBT.available()) {
    // Lê o JSON da comunicação Bluetooth
    String jsonString = SerialBT.readStringUntil('\n');
    Serial.print(".");
    // Envia o JSON pela comunicação serial
    Serial.println(jsonString);
  }
}