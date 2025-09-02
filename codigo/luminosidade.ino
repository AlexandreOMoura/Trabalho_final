#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

// Pino do sensor LDR
#define ldrPin A0

// Pinos do driver L298N
const int motorEsq_IN1 = 0;
const int motorEsq_IN2 = 1;
const int motorDir_IN3 = A5;
const int motorDir_IN4 = A6;
const int enable_A = 2;
const int enable_B = 3;

// Limite de intensidade de luz para avançar
const int limiarLuz = 500; // ajuste após teste

void setup() {
  carrier.noCase();
  carrier.begin();

  // LDR
  pinMode(ldrPin, INPUT);

  // Motores
  pinMode(motorEsq_IN1, OUTPUT);
  pinMode(motorEsq_IN2, OUTPUT);
  pinMode(motorDir_IN3, OUTPUT);
  pinMode(motorDir_IN4, OUTPUT);

  // Enable
  pinMode(enable_A, OUTPUT);
  pinMode(enable_B, OUTPUT);

  carrier.leds.clear();
  for (int i = 0; i < 5; i++) {
    carrier.leds.setPixelColor(i, 0, 0, 255);
  }
  carrier.leds.setBrightness(255);
  carrier.leds.show();

  stop();

  for (int i = 0; i < 3; i++) {
    carrier.Buzzer.beep(800, 500);
    delay(500);
  }
}

void loop() {
  int luz = analogRead(ldrPin);
  Serial.print("Intensidade da luz: ");
  Serial.println(luz);

  // Decisão de movimento
  if (luz > limiarLuz) {
    forward(); // luz intensa → seguir em frente
  } else if (luz > limiarLuz / 2) {
    right();   // luz média → virar à direita
  } else {
    left();    // luz baixa → virar à esquerda
  }

  delay(200);
}

// ===== Funções de movimento =====
void forward() {
  digitalWrite(motorEsq_IN1, HIGH);
  digitalWrite(motorEsq_IN2, LOW);
  digitalWrite(motorDir_IN3, HIGH);
  digitalWrite(motorDir_IN4, LOW);
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
}

void right() {
  digitalWrite(motorEsq_IN1, HIGH);
  digitalWrite(motorEsq_IN2, LOW);
  digitalWrite(motorDir_IN3, LOW);
  digitalWrite(motorDir_IN4, HIGH);
  analogWrite(enable_A, 200);
  analogWrite(enable_B, 200);
}

void left() {
  digitalWrite(motorEsq_IN1, LOW);
  digitalWrite(motorEsq_IN2, HIGH);
  digitalWrite(motorDir_IN3, HIGH);
  digitalWrite(motorDir_IN4, LOW);
  analogWrite(enable_A, 200);
  analogWrite(enable_B, 200);
}

void stop() {
  analogWrite(enable_A, 0);
  analogWrite(enable_B, 0);
}
