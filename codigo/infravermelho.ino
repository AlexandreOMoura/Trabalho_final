#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

// Definições dos sensores IR em modo digital
const int sensorIR_Esq = A4;                       // Pino digital para o sensor IR Esquerdo
const int sensorIR_Dir = A3;                       // Pino digital para o sensor IR Direito

// Definições dos pinos do sensor HC-SR04
const int trigPin = 9;                            // Pino digital trigger do sensor de ultrasons
const int echoPin = 10;                           // Pino digital eco do sensor de ultrasons






// Definições dos pinos do driver L298N
const int motorEsq_IN1 = 0;                       // Pino digital Frente motor Esq
const int motorEsq_IN2 = 1;                       // Pino digital Traz motor Esq
const int motorDir_IN3 = A5;                       // Pino digital Frente motor Dir
const int motorDir_IN4 = A6;                       // Pino digital Traz motor Dir
const int enable_A = 2;                           // Pino analogico (PWM) para controle de velocidade do motor esquerdo
const int enable_B = 3;                           // Pino analogico (PWM) para controle de velocidade do motor direito






// Limiar para detecção de obstáculos
const float distanciaObstaculo = 10.0;  // Distância de parada em centímetros


void setup() {

 carrier.noCase();
 carrier.begin();

 // Sensores IR
 pinMode(sensorIR_Esq, INPUT);                   //Configura o pino para se comportar como uma entrada ou uma saída (Receber = INPUT)
 pinMode(sensorIR_Dir, INPUT);                   //Configura o pino para se comportar como uma entrada ou uma saída (Receber = INPUT)

 // Sensor HC-SR04
 pinMode(trigPin, OUTPUT);                       //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)
 pinMode(echoPin, INPUT);                        //Configura o pino para se comportar como uma entrada ou uma saída (Receber = INPUT)

 // Motores
 pinMode(motorEsq_IN1, OUTPUT);                  //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)
 pinMode(motorEsq_IN2, OUTPUT);                  //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)
 pinMode(motorDir_IN3, OUTPUT);                  //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)
 pinMode(motorDir_IN4, OUTPUT);                  //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)

 // Pinos enable para controle de velocidade
 pinMode(enable_A, OUTPUT);                      //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)
 pinMode(enable_B, OUTPUT);                      //Configura o pino para se comportar como uma entrada ou uma saída (Mandar = OUTPUT)

 carrier.leds.clear();

 for (int i = 0; i<5; i++){
   carrier.leds.setPixelColor(i, 0, 0, 255);
 }
 
 carrier.leds.setBrightness(255);
 carrier.leds.show();

 digitalWrite(motorEsq_IN1, HIGH);
 digitalWrite(motorEsq_IN2, LOW);

 digitalWrite(motorDir_IN3, HIGH);
 digitalWrite(motorDir_IN4, LOW);

 stop();

 for (int i = 0; i<3; i++){

   carrier.Buzzer.beep(800, 500);
   delay(500);
 }
}

void loop() {
 // Lê os valores dos sensores IR (foraLinhaEsquerda é true quando o sensor mede HIGH)
 boolean foraLinhaEsquerda = digitalRead(sensorIR_Esq) == HIGH;    //HIGH corresponde a linha preta;LOW corresponde a linha branca
 boolean foraLinhaDireita  = digitalRead(sensorIR_Dir) == HIGH;    //HIGH corresponde a linha preta;LOW corresponde a linha branca


 // Lê a distância do sensor de ultrassom
 // float distance_cm = getDistance();
 
 /*
 Serial.println("---------------");
 Serial.print("Esquerda: ");
 Serial.print(foraLinhaEsquerda);
 Serial.print(" Direita: ");
 Serial.println(foraLinhaDireita);
 */

 // Decisão de movimento baseada nos sensores IR e de ultrassom
 /*
 if (distance_cm <= distanciaObstaculo) {
   stop(); // Para o robô se houver um obstáculo
 }
 */
 if (foraLinhaEsquerda && foraLinhaDireita) {              //se o inverso de foraLinhaEsquerda (false=0=LOW) e foraLinhaDireita (true=1=HIGH) acontecerem então...
   right(); // Sensor direito fora da linha: vire à esquerda
 }else if (!foraLinhaEsquerda && !foraLinhaDireita) {              //se o inverso de foraLinhaEsquerda (false=0=LOW) e inverso de foraLinhaDireita (true=0=LOW) acontecerem então...
   left(); 
 }else {
   forward(); // Ambos os sensores sobre a linha: siga em frente
 }
 
}

// Funções para controlar os motores
void forward() {

 analogWrite(enable_A, 255);
 analogWrite(enable_B, 255);
}

void right() {

 analogWrite(enable_A, 0);
 analogWrite(enable_B, 100);
}

void left() {
 
 analogWrite(enable_A, 100);
 analogWrite(enable_B, 0);
}

void stop() {

 analogWrite(enable_A, 0);
 analogWrite(enable_B, 0);
}

// Função para medir a distância usando o sensor de ultrassom
float getDistance() {

 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

 long duration = pulseIn(echoPin, HIGH);

 if ((duration * 0.034 / 2) != 0){
   return duration * 0.034 / 2;
 }
}


