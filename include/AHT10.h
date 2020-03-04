#ifndef __AHT10_H
#define __AHT10_H

class AHT10 {
public:
  static bool begin();
  static bool reset();
  static bool measure(float *temp, float *hum);
  static float getTemperature();
  static float getHumidity();
};

#endif
