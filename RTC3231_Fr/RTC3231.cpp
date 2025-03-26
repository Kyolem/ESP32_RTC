#include <RTC3231.h>

const char *month[] = {"Nat", "Jan", "Fev", "Mar", "Avr", "Mai", "Jun", "Jui", "Aou", "Sep", "Oct", "Nov", "Dec"};
const char *days[] = {"Nat", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

RTC3231 ::RTC3231()
{
    _adress = 0;
}
//************************************
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
//*****************************************
void RTC3231::setTime(uint8_t hh, uint8_t mm, uint8_t ss)
{
    Wire.beginTransmission(_adress);
    Wire.write(RTC3231_SECOND_REG);
    Wire.write(_binToBcd(ss));
    Wire.write(_binToBcd(mm));
    Wire.write(_binToBcd(hh));
    Wire.endTransmission();
}
//************************************************************************
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
String RTC3231::getStringTime() // hh:mm:ss
{
    char Time[] = "00:00:00";
    sprintf(Time, "%02d:%02d:%02d", getHour(), getMinute(), getSecond());
    return String(Time);
}
String RTC3231::getStringDate() // hh:mm:ss
{
    char Date[] = "00/00/0000";
    sprintf(Date, "%02d/%s/20%02d", getDay(), getStringMonth(), getYears());
    return String(Date);
}
