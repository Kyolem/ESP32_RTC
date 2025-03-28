#include <Arduino.h>
#include "Wire.h"
#include <Ticker.h>
#include "RTC3231.h"

#define DS3231 0x68

RTC3231 RTC;

const uint32_t PERIOD = 1000;

void action(void);

Ticker myTick(action, PERIOD, 0, MILLIS);

void action()
{
  Serial.println(RTC.getStringTime());
  Serial.println(RTC.getStringDate());
}
void setup()
{
  RTC.begin(DS3231);
  Serial.begin(115200);
  Wire.begin();
  myTick.start();
  RTC.setDate(F(__DATE__), 5);
  RTC.setTime(F(__TIME__));
}

void loop()
{
  myTick.update();
}
