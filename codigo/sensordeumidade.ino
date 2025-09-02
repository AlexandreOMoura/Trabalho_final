#define moisturePin A0  // Pino analógico do sensor
#define ledPin 2        // LED indicador
#define buzzerPin 3     // Buzzer

int moistureValue = 0;  // Valor lido do sensor

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.println("Monitoramento do Sensor de Umidade do Solo");
  Serial.println("------------------------------------------------");
}

void loop() {
  // Lê valor do sensor
  moistureValue = analogRead(moisturePin);

  // Mostra valor no Serial
  Serial.print("Umidade do solo: ");
  Serial.print(moistureValue);

  // Lógica para LED e buzzer
  if (moistureValue < 400) {  // Solo SECO
    Serial.println("  --> Solo SECO");
    digitalWrite(ledPin, HIGH);     // LED aceso
    digitalWrite(buzzerPin, HIGH);  // Buzzer ligado
  } 
  else if (moistureValue >= 400 && moistureValue < 700) {  // Solo ÚMIDO
    Serial.println("  --> Solo ÚMIDO");
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  } 
  else {  // Solo MOLHADO
    Serial.println("  --> Solo MOLHADO");
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000); // pausa de 1 segundo
}
