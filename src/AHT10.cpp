#include <Arduino.h>
#include <Wire.h>
#include "AHT10.h"

static const uint8_t AHT10_ADDR = 0x38;

bool AHT10::begin() {
  Wire.beginTransmission(AHT10_ADDR);
  Wire.write(0xE1);
  Wire.write(0x08);
  Wire.write(0x00);
  return Wire.endTransmission() == 0;
}

bool AHT10::reset() {
  Wire.beginTransmission(AHT10_ADDR);
  Wire.write(0xBA);
  return Wire.endTransmission() == 0;
}

bool AHT10::measure(float *temp, float *hum) {
  uint8_t data[6];
  uint32_t d;

  Wire.beginTransmission(AHT10_ADDR);
  Wire.write(0xAC);
  Wire.write(0x33);
  Wire.write(0x00);
  if (Wire.endTransmission())
    return false;
  delay(75);
  if ((Wire.requestFrom(AHT10_ADDR, (uint8_t)6) != 6) || (Wire.readBytes(data, 6) != 6))
    return false;
  if (temp) {
    d = ((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
    *temp = (float)d * 200 / 1048576 - 50;
  }
  if (hum) {
    d = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    *hum = (float)d * 100 / 1048576;
  }
  return true;
}

float AHT10::getTemperature() {
  float result;

  if (! measure(&result, NULL))
    result = NAN;
  return result;
}

float AHT10::getHumidity() {
  float result;

  if (! measure(NULL, &result))
    result = NAN;
  return result;
}
