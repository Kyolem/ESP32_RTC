/**************************************************************************/
/*!
  @file     RTC3231.cpp

  @mainpage Kyolem RTC3231

  @section intro Introduction

  This is a work of Kyolem fantastic real time clock library for Arduino.

  @section classes Available classes

  This library provides the following classes:

  - Classes for manipulating dates, times and durations:
    - RTC3231 represents a specific point in time; this is the data
      type used for setting and reading the supported RTCs
  - Interfacing specific RTC chips:
    - RTC_DS3231
*/
/**************************************************************************/

#include <RTC3231.h>

const char *month[] = {"Nat", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const char *days[] = {"Nat", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

RTC3231 ::RTC3231()
{
    _adress = 0;
}
/**************************************************************************/
/*!
    @brief  Fonction for begin the RTC3231 transmission.
    We use the Wire library to begin the transmission with the RTC3231 module.
    @warning If the provided parameters are not valid it automatically returns false.
    @return true if the transmission is ok, false if not.
    @see   The `isValid()` method can be used to test whether the
           constructed DateTime is valid.
    @param adress adress in uint8_t like 0x68 in general.
*/
/**************************************************************************/
bool RTC3231 ::begin(uint8_t adress)
{
    _adress = adress; // chaque objet aura sa propre adresse
    bool res = false;
    Wire.begin();
    Wire.beginTransmission(adress);
    uint8_t val = Wire.endTransmission();
    if (val == 0)
    {
        res = true;
    }
    else
    {
        res = false;
    }
    return res;
}
//***************************************
uint8_t RTC3231::_binToBcd(uint8_t val)
{
    return ((val / 10 * 16) + (val % 10));
}
//***************************************
uint8_t RTC3231::_bcdToBin(uint8_t val)
{
    return ((val / 16 * 10) + (val % 16));
}
/**************************************************************************/
/*!
    @brief  Fonction to set the time in the RTC3231 module.
    @param hh hours in uint8_t.
    @param mm minutes in uint8_t.
    @param ss seconds in uint8_t.
*/
/**************************************************************************/
void RTC3231::setTime(uint8_t hh, uint8_t mm, uint8_t ss)
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_SECOND_REG);
    Wire.write(_binToBcd(ss));
    Wire.write(_binToBcd(mm));
    Wire.write(_binToBcd(hh));
    Wire.endTransmission();
}
/**************************************************************************/
/*!
    @brief  Fonction to set the time in the RTC3231 module.
    @param Time time in __FlashStringHelper like "hh:mm:ss".
*/
/**************************************************************************/
void RTC3231::setTime(const __FlashStringHelper *Time)
{
    uint8_t hh = 0, mm = 0, ss = 0;
    String timeStr = String(Time);
    sscanf(timeStr.c_str(), "%d:%d:%d", &hh, &mm, &ss);
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_SECOND_REG);
    Wire.write(_binToBcd(ss));
    Wire.write(_binToBcd(mm));
    Wire.write(_binToBcd(hh));
    Wire.endTransmission();
}
/**************************************************************************/
/*!
    @brief  Fonction to set the date in the RTC3231 module.
    @param index_day index of the day in uint8_t.
    @param day day in uint8_t.
    @param index_month index of the month in uint8_t.
    @param years years in uint8_t.
*/
/**************************************************************************/
void RTC3231::setDate(uint8_t index_day, uint8_t day, uint8_t index_month, uint8_t years)
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_DAY_REG);
    Wire.write(_binToBcd(index_day));
    Wire.write(_binToBcd(day));
    Wire.write(_binToBcd(index_month));
    Wire.write(_binToBcd(years));
    Wire.endTransmission();
}
/**************************************************************************/
/*!
    @brief  Fonction to set the date in the RTC3231 module.
    @param Date date in __FlashStringHelper like "dd/mm/yyyy".
    @param index_day index of the day in uint8_t like 1 for monday and etc.
*/
/**************************************************************************/
void RTC3231::setDate(const __FlashStringHelper *Date, uint8_t index_day)
{
    uint8_t day = 0, index_month = 0, years = 0;
    String dateStr = String(Date);
    index_month = _getindexmonth(Date);
    char poubelle[3];
    day = _twodigittoone(Date);
    sscanf(dateStr.c_str(), "%s/%d/%d", &poubelle, &day, &years);
    day = _twodigittoone(Date);
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_DAY_REG);
    Wire.write(_binToBcd(index_day));
    Wire.write(_binToBcd(day));
    Wire.write(_binToBcd(index_month));
    Wire.write(_binToBcd(years - 2000U));
    Wire.endTransmission();
}
/**************************************************************************/
/*!
    @brief  Fonction to get the years in the RTC3231 module.
    @return years in uint8_t.
*/
/**************************************************************************/
uint8_t RTC3231::getYears() // yy
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_YEAR_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return val;
}
/**************************************************************************/
/*!
    @brief  Fonction to get the hour in the RTC3231 module.
    @return hour in uint8_t.
*/
/**************************************************************************/
uint8_t RTC3231::getHour() // hh
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_HOURS_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = val & 0x3f;
    val = _bcdToBin(val);
    return val;
}
/**************************************************************************/
/*!
    @brief  Fonction to get the minute in the RTC3231 module.
    @return minute in uint8_t.
*/
/**************************************************************************/
uint8_t RTC3231::getMinute() // mm
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_MINUTE_REG);
    Wire.endTransmission();
    //
    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return val;
}
/**************************************************************************/
/*!
    @brief  Fonction to get the second in the RTC3231 module.
    @return second in uint8_t.
*/
/**************************************************************************/
uint8_t RTC3231::getSecond() // ss
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_SECOND_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return val;
}
/**************************************************************************/
/*!
    @brief  Fonction to get the day string in the RTC3231 module.
    @return day in String.
*/
/**************************************************************************/
String RTC3231::getStringDay() // Dim, lun, Mar, Mer, Jeu, Ven, Sam,
{

    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_DAY_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return String(days[val]);
}
/**************************************************************************/
/*!
    @brief  Fonction to get the day in the RTC3231 module.
    @return day in uint8_t.
*/
/**************************************************************************/
uint8_t RTC3231::getDay() // 1 to 31
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_DATE_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return val;
}
/**************************************************************************/
/*!
    @brief  Fonction to get the month string in the RTC3231 module.
    @return month in String.
*/
/**************************************************************************/
String RTC3231::getStringMonth() // Jan, Fev, Mars, Avril, Mai, Juin, Juil, Aout, Sept, Oct, Nov, Dec
{

    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_MONTH_REG);
    Wire.endTransmission();

    Wire.requestFrom(_adress, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission();
    val = _bcdToBin(val);
    return String(month[val]);
}
/**************************************************************************/
/*!
    @brief  Fonction to get the time string in the RTC3231 module.
    @return time in String like 00:00:00.
*/
/**************************************************************************/
String RTC3231::getStringTime() // hh:mm:ss
{
    char Time[] = "00:00:00";
    sprintf(Time, "%02d:%02d:%02d", getHour(), getMinute(), getSecond());
    return String(Time);
}
/**************************************************************************/
/*!
    @brief  Fonction to get the date string in the RTC3231 module.
    @return date in String like 00/00/0000.
*/
/**************************************************************************/
String RTC3231::getStringDate() // hh:mm:ss
{
    char Date[] = "00/00/0000";
    sprintf(Date, "%02d/%s/20%02d", getDay(), getStringMonth(), getYears());
    return String(Date);
}

uint8_t RTC3231::_getindexmonth(const __FlashStringHelper *Date)
{
    uint8_t index_month = 0;

    if (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
    {
        index_month = 1;
    }
    else if (__DATE__[0] == 'F' && __DATE__[1] == 'e' && __DATE__[2] == 'v')
    {
        index_month = 2;
    }
    else if (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
    {
        index_month = 3;
    }
    else if (__DATE__[0] == 'A' && __DATE__[1] == 'p' && __DATE__[2] == 'r')
    {
        index_month = 4;
    }
    else if (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
    {
        index_month = 5;
    }
    else if (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
    {
        index_month = 6;
    }
    else if (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
    {
        index_month = 7;
    }
    else if (__DATE__[0] == 'A' && __DATE__[1] == 'u' && __DATE__[2] == 'g')
    {
        index_month = 8;
    }
    else if (__DATE__[0] == 'S' && __DATE__[1] == 'e' && __DATE__[2] == 'p')
    {
        index_month = 9;
    }
    else if (__DATE__[0] == 'O' && __DATE__[1] == 'c' && __DATE__[2] == 't')
    {
        index_month = 10;
    }
    else if (__DATE__[0] == 'N' && __DATE__[1] == 'o' && __DATE__[2] == 'v')
    {
        index_month = 11;
    }
    else if (__DATE__[0] == 'D' && __DATE__[1] == 'e' && __DATE__[2] == 'c')
    {
        index_month = 12;
    }
    return index_month;
}
uint8_t RTC3231::_twodigittoone(const __FlashStringHelper *Date)
{
    uint8_t day = 0;
    if (__DATE__[4] == '0')
    {
        day = __DATE__[5];
    }
    return day;
}
