#include <Arduino.h> // Includes the Arduino core library for basic functionality.
#include <Wire.h>   // Includes the Wire library for I2C communication.
#include <Ticker.h>  // Includes the Ticker library for periodic function execution.
#include <RTC3231_En.h> // Includes the RTC3231 library for interacting with the DS3231 RTC module.

#define DS3231 0x68 // Defines the I2C address of the DS3231 RTC module.

RTC3231 RTC; // Creates an instance of the RTC3231 class to interact with the RTC module.

const uint32_t PERIOD = 1000; // Defines the period (in milliseconds) for the Ticker to trigger.

void action(void); // Declares the function `action` that will be called periodically by the Ticker.

Ticker myTick(action, PERIOD, 0, MILLIS);
// Creates a Ticker object that calls the `action` function every `PERIOD` milliseconds.
// The `0` indicates it will run indefinitely, and `MILLIS` specifies the time unit.

void action()
{
  Serial.println(RTC.getStringTime()); // Prints the current time as a string to the Serial Monitor.
  Serial.println(RTC.getStringDate()); // Prints the current date as a string to the Serial Monitor.
}

void setup()
{
  RTC.begin(DS3231);    // Initializes the RTC module with the specified I2C address.
  Serial.begin(115200); // Starts the Serial communication at a baud rate of 115200.
  Wire.begin();         // Initializes the I2C communication.
  myTick.start();       // Starts the Ticker to begin calling the `action` function periodically.
  RTC.setDate(F(__DATE__), 5);
  // Sets the RTC date using the compile date (`__DATE__`) and a day of the week (5 = Friday).
  RTC.setTime(F(__TIME__));
  // Sets the RTC time using the compile time (`__TIME__`).
}

void loop()
{
  myTick.update();
  // Updates the Ticker, checking if the `action` function needs to be called.
}
