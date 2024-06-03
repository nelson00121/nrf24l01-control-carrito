#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[4] = "00004";

// Pines para el puente H (reajustados)
//Para el lado A...
const int ENA = 7;
const int IN1 = 3;
const int IN2 = 4;
//Para el lado B...
const int ENB = 8;
const int IN3 = 5;
const int IN4 = 6;
//ENA IN1,IN2  //ENB IN3,IN4


void setup() {
  Serial.begin(1600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  // Configurar pines del puente H como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Detener los motores al inicio
  //stopMotors();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Mensaje recibido: ");
    Serial.println(text);

    if (strcmp(text, "Izquierda") == 0) {
      // Gira a la izquierda
      Serial.println("Girando a la izquierda");//ENA IN1,IN2  //ENB IN3,IN4
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (strcmp(text, "Derecha") == 0) {
      // Gira a la derecha
      Serial.println("Girando a la derecha");
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (strcmp(text, "Adelante") == 0) {
      // Avanza hacia adelante
      Serial.println("Avanzando hacia adelante");
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (strcmp(text, "Atras") == 0) {
      // Retrocede hacia atrás
      Serial.println("Retrocediendo hacia atrás");
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {
      // Si no hay una dirección específica, detener motores
      Serial.println("Deteniendo motores");
      stopMotors();
    }
  } else {
    // Si no hay datos disponibles, detener los motores
    stopMotors();
  }
}

void stopMotors() {
  Serial.println("Motores detenidos");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


