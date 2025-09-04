#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup() {
  // Inicia a comunicação serial e o carrier
  Serial.begin(115200);
  CARRIER_CASE = false;  // se usar a case oficial, troque para true
  carrier.begin();

  // Configuração inicial do display
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(ST77XX_WHITE);
}

void loop() {
  // ---- Temperatura ----
  float tempC = carrier.Env.readTemperature();
  float tempF = carrier.Env.readTemperature(FAHRENHEIT);

  // ---- Pressão Atmosférica ----
  float pressure = carrier.Pressure.readPressure(); // hPa

  // ---- Acelerômetro ----
  float x, y, z;
  if (carrier.IMUmodule.accelerationAvailable()) {
    carrier.IMUmodule.readAcceleration(x, y, z);
  }

  // ---- Serial Monitor ----
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" C | ");
  Serial.print(tempF);
  Serial.println(" F");

  Serial.print("Pressao: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Accel -> X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  Serial.println("--------------------------");

  // ---- Display ----
  carrier.display.fillScreen(ST77XX_BLACK);

  carrier.display.setCursor(25, 50);
  carrier.display.print("Temp: ");
  carrier.display.print(tempC);
  carrier.display.println(" C");

  carrier.display.setCursor(25, 80);
  carrier.display.print("Press: ");
  carrier.display.print(pressure);
  carrier.display.println(" hPa");

  carrier.display.setCursor(25, 100);
  carrier.display.print("Acc X:");
  carrier.display.print(x, 1);

  carrier.display.setCursor(25, 150);
  carrier.display.print("Y:");
  carrier.display.print(y, 1);

  carrier.display.setCursor(25, 180);
  carrier.display.print("Z:");
  carrier.display.print(z, 1);

  delay(100);
}
