#include <Arduino.h>
#include <Servo.h>

// Pinos ultrassom
const int trigPin = 2;
const int echoPin = 3;
// Variáveis para armazenar o tempo de ida e volta do sinal ultrassônico
long duration;
int distance;

// Servo motor
Servo meuServo;  // Cria um objeto do tipo Servo para controlar um servo motor
int pos = 0;     // Variável para armazenar a posição atual do servo motor
int servoPin = 10;

void sonar() {
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

  // Imprime a distância no Monitor Serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void varredura() {
  // Faz a varredura de 90 graus para um lado
  for (pos = 90; pos >= 0; pos -= 1) {
    meuServo.write(pos);
    sonar();
  }

  // Faz a varredura de 90 graus para o outro lado
  for (pos = 0; pos <= 180; pos += 1) {
    meuServo.write(pos);
    sonar();  
  }

  for (pos = 180; pos >= 90; pos -= 1) {
    meuServo.write(pos);
    delay(15);
    Serial.println("-");
  }
}



void setup() {
  Serial.begin(9600);
  meuServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  varredura();
  delay(1000);
}