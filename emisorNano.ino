#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
//PINES DE NRF24L01
//GND
//VCC
//PIN  CE 9
//PIN CSN 10
//PIN SCK 13
//PIN MOSI 11
//PIN MISO 12
const byte address[4] = "00004";

const int VRy = A0;  // Pin analógico para el eje Y
const int VRx = A1;  // Pin analógico para el eje X
const int SW = 2;    // Pin digital para el botón del joystick (opcional)

void setup() {
  Serial.begin(1600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  pinMode(SW, INPUT_PULLUP); // Configura el pin del botón con pull-up interno
}

void loop() {
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);
  int buttonState = digitalRead(SW);

  String direction = "";

  // Determinar la dirección del movimiento
  if (xValue < 400) {
    direction = "Izquierda";
  } else if (xValue > 600) {
    direction = "Derecha";
  }

  if (yValue < 400) {
    direction = "Abajo";
  } else if (yValue > 600) {
    direction = "Arriba";
  }

  // Detectar si el botón está presionado
  if (buttonState == LOW) {
    direction = "Botón presionado";
  }

  if (direction != "") {
    radio.write(direction.c_str(), direction.length() + 1);
    Serial.println("Mensaje enviado: " + direction);
  }

  delay(200); 
  // Pequeño retardo para no saturar el puerto serie
}



