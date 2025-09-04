#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

void setup() {
  Serial.begin(115200);
  CARRIER_CASE = false;  
  carrier.begin();

  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setCursor(10, 20);
  carrier.display.print("Monitor Ambiente");
  delay(2000);
}

void loop() {
  float temp = carrier.Env.readTemperature();
  float hum  = carrier.Env.readHumidity();

  // Mostrar no display
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setCursor(30, 80);
  carrier.display.print("Temp: ");
  carrier.display.print(temp);
  carrier.display.println(" C");

  carrier.display.setCursor(30, 120);
  carrier.display.print("Umid: ");
  carrier.display.print(hum);
  carrier.display.println(" %");

  // LEDs mudam conforme umidade
  if (hum < 40) {
    carrier.leds.fill(255, 0, 0);   // Vermelho - ar seco
  } else if (hum < 60) {
    carrier.leds.fill(0, 255, 0);   // Verde - ideal
  } else {
    carrier.leds.fill(0, 0, 255);   // Azul - úmido
  }
  carrier.leds.show();

  delay(2000);
}
