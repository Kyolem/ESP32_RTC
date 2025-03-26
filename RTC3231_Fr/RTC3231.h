#ifndef RTC3231_H
#define RTC3231_H

#include <Arduino.h>
#include <Wire.h>

// les registres

#define RTC3231_SECOND_REG 0x00
#define RTC3231_MINUTE_REG 0x01
#define RTC3231_HOURS_REG 0x02
#define RTC3231_DAY_REG 0x03
#define RTC3231_DATE_REG 0x04
#define RTC3231_MONTH_REG 0x05
#define RTC3231_YEAR_REG 0x06

class RTC3231
{

public:
    // constructeur
    RTC3231();

    // méthodes
    bool begin(uint8_t Adress);

    void setTime(uint8_t hh, uint8_t mm, uint8_t ss);
    void setDate(uint8_t index_day, uint8_t day, uint8_t index_month, uint8_t years);

    uint8_t getYears();  // yy
    uint8_t getHour();   // hh
    uint8_t getMinute(); // mm
    uint8_t getSecond(); // ss
    uint8_t getDay();    // 1 to 31

    String getStringDay();   // Dim, lun, Mar, Mer, Jeu, Ven, Sam,
    String getStringMonth(); // Jan, Fev, Mars, Avril, Mai, Juin, Juil, Aout, Sept, Oct, Nov, Dec
    String getStringTime();  // hh:mm:ss
    String getStringDate();  // day/mois/year

private:
    uint8_t _adress;
    uint8_t _binToBcd(uint8_t val);
    uint8_t _bcdToBin(uint8_t val);
};

#endif