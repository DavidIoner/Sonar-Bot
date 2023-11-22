#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);  // Baud rate de 9600
  SerialBT.begin("ESP32_BT"); // Nome do dispositivo Bluetooth
}

void loop() {
  if (Serial.available()) {
    // Lê o JSON da comunicação serial
    String jsonString = Serial.readStringUntil('\n');
    
    // Envia o JSON pela comunicação Bluetooth
    SerialBT.println(jsonString);

  }
}