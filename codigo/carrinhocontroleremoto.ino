#include <Arduino_MKRIoTCarrier.h>
#include <IRremote.h>   // Biblioteca para o HX1838

MKRIoTCarrier carrier;

// Definições do receptor HX1838
const int RECV_PIN = 11;    // Saída de sinal do HX1838 conectada no D11
IRrecv irrecv(RECV_PIN);
decode_results results;

// Definições dos pinos do sensor HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Definições dos pinos do driver L298N
const int motorEsq_IN1 = 0;
const int motorEsq_IN2 = 1;
const int motorDir_IN3 = A5;
const int motorDir_IN4 = A6;
const int enable_A = 2;
const int enable_B = 3;

// Limiar para detecção de obstáculos
const float distanciaObstaculo = 10.0;

void setup() {
  carrier.noCase();
  carrier.begin();

  // Inicializa receptor IR
  irrecv.enableIRIn();
  Serial.begin(9600);

  // Sensor HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motores
  pinMode(motorEsq_IN1, OUTPUT);
  pinMode(motorEsq_IN2, OUTPUT);
  pinMode(motorDir_IN3, OUTPUT);
  pinMode(motorDir_IN4, OUTPUT);

  // Pinos enable (PWM)
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
  if (irrecv.decode(&results)) {
    long codigo = results.value;
    Serial.println(codigo, HEX); // Mostra no monitor serial

    // Substitua os valores pelos códigos do SEU controle remoto
    if (codigo == 0xFF629D) { // Botão "frente"
      forward();
    } else if (codigo == 0xFFA857) { // Botão "trás"
      backward();
    } else if (codigo == 0xFF22DD) { // Botão "esquerda"
      left();
    } else if (codigo == 0xFFC23D) { // Botão "direita"
      right();
    } else if (codigo == 0xFF02FD) { // Botão "OK" (parar)
      stop();
    }

    irrecv.resume(); // Prepara para o próximo sinal
  }
}

// Funções para controlar os motores
void forward() {
  digitalWrite(motorEsq_IN1, HIGH);
  digitalWrite(motorEsq_IN2, LOW);
  digitalWrite(motorDir_IN3, HIGH);
  digitalWrite(motorDir_IN4, LOW);
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
}

void backward() {
  digitalWrite(motorEsq_IN1, LOW);
  digitalWrite(motorEsq_IN2, HIGH);
  digitalWrite(motorDir_IN3, LOW);
  digitalWrite(motorDir_IN4, HIGH);
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

// Função para medir a distância (mantida do seu código)
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  if ((duration * 0.034 / 2) != 0) {
    return duration * 0.034 / 2;
  }
}
