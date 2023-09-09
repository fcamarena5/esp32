#include <OneWire.h>
#include <DallasTemperature.h>


int oneWireBus = 27;
int pinLDR = A14;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void init_sensors() {
  sensors.begin();
  pinMode(pinLDR, INPUT);
}

float get_temperature() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temp);
  return temp;
}

int get_light() {
  int ilum = analogRead(pinLDR);
  Serial.print("Light: ");
  Serial.println(ilum);
  return ilum;
}
