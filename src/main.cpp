#include <Arduino.h>
#include <Wire.h>
#include "AHT10.h"

void setup() {
  Serial.begin(115200);
  Serial.println();

  Wire.begin();
  if (! AHT10::begin()) {
    Serial.println(F("AHT10 not detected!"));
    Serial.flush();
    ESP.deepSleep(0);
  }
}

void loop() {
  float temp, hum;

  delay(2000);
  if (AHT10::measure(&temp, &hum)) {
    Serial.print(F("Temperature is "));
    Serial.print(temp);
    Serial.print(F(" C, humidity is "));
    Serial.print(hum);
    Serial.println('%');
  } else {
    Serial.println(F("AHT10 read error!"));
  }
}
