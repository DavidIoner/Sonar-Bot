#include <Arduino.h>
#include <Servo.h>
#include <ArduinoJson.h>

// Pinos ultrassom
const int trigPin = 2;
const int echoPin = 3;
// Variáveis para armazenar o tempo de ida e volta do sinal ultrassônico
long duration;
int distance;

// Servo motor
Servo meuServo; 
int pos = 0;     
int servoPin = 10;

// Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int direita;
int esquerda;
int centro;

void moviment(String direction) {
  if (direction == "centro") {
    //Gira o Motor A no sentido horario
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //girar motor b no sentido horário
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);
  }
  if (direction == "re") {
    // M1
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    // M2
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
  }
  if (direction == "direita") {
    moviment("re");
    delay(1000);
    // M1
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    // M2
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
    delay(300);
  }
  if (direction == "esquerda") {
    moviment("re");
    delay(1000);
    // M1
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    // M2
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);
    delay(300);
  }
  // ----------------------------------------------------------------
  // CONFERIR ISSO!!!!!!!!!!!!
  // ---------------------------------------------------------------- 
  if (direction == "parar") {
    // M1
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    // M2
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, HIGH);
  }
}


void toEsp(int distancia, int angulo){
  StaticJsonDocument<200> doc;
  
  // Adiciona dados ao JSON (por exemplo, um contador)
  doc["angulo"] = angulo;
  doc["distancia"] = distancia;
  
  // Serializa o JSON para uma string
  String jsonString;
  serializeJson(doc, jsonString);

  // Envia ao esp32
  Serial.println(jsonString);
}

int sonar() {
  // Gera um pulso ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede o tempo de ida e volta do sinal
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2;

  return distance;
}

String varredura() {
  // Faz a varredura de 90 graus para um lado
  for (pos = 90; pos >= 0; pos -= 3) {
    meuServo.write(pos);
    toEsp(sonar(), pos);
    if (pos == 0){
      delay(30);
      direita = sonar();
    }   
    delay(30);
  }

  // Faz a varredura de 90 graus para o outro lado
  for (pos = 0; pos <= 180; pos += 3) {
    meuServo.write(pos);
    toEsp(sonar(), pos);
    if (pos == 180){
      delay(30);
      esquerda = sonar();
    }
    delay(30);
  }

  for (pos = 180; pos >= 90; pos -= 3) {
    meuServo.write(pos);
    delay(10);
  }
  // calcula a melhor distancia
  if (esquerda > direita){
    return "esquerda";
  } else {
    return "direita";
  }
}


void setup() {
  Serial.begin(9600);
  meuServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (sonar() <= 30) {
    moviment("parar");
    moviment(varredura());
  }
  moviment("centro");
  delay(100);
  varredura();
}