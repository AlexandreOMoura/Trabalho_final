#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

// Pinos do sensor ultrassônico
const int trigPin = 9;
const int echoPin = 10;

// Pinos do driver L298N
const int motorEsq_IN1 = 0;
const int motorEsq_IN2 = 1;
const int motorDir_IN3 = A5;
const int motorDir_IN4 = A6;
const int enable_A = 2;
const int enable_B = 3;

// Distância mínima para parar (cm)
const float distanciaObstaculo = 15.0;

void setup() {
  carrier.noCase();
  carrier.begin();

  // Sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motores
  pinMode(motorEsq_IN1, OUTPUT);
  pinMode(motorEsq_IN2, OUTPUT);
  pinMode(motorDir_IN3, OUTPUT);
  pinMode(motorDir_IN4, OUTPUT);

  // Enable (PWM)
  pinMode(enable_A, OUTPUT);
  pinMode(enable_B, OUTPUT);

  // LEDs do Carrier
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
  float distance_cm = getDistance();
  Serial.print("Distância: ");
  Serial.println(distance_cm);

  // Decisão de movimento baseada na distância
  if (distance_cm <= distanciaObstaculo) {
    stop();           // Para se houver obstáculo
    delay(500);       // pequena pausa
    right();          // desvia para a direita
    delay(400);       // tempo para virar
    forward();        // segue em frente
  } else {
    forward();        // segue normalmente
  }
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

// ===== Função para medir distância =====
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // cm
  return distance;
}
