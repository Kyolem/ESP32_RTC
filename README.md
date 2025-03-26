# ESP32_RTC
#### This is a library to use a DS3231 with many microcontroller
#### You have diffferent fonction with their uses :

` bool begin(uint8_t Adress) ` 
This fonction is use to begin the transmission with the DS3231's adress.    
She return True for no problem and False if there is a problem.

` void setTime(uint8_t hh, uint8_t mm, uint8_t ss) `   
This fonction is use to set the time.  
To set the actual Time you have to put in order :  
The hours : 0 ... 24.  
The minutes: 0 ... 59.    
And the seconds : 0 ... 59.
> I don't have make an auto time set fonction yet.

` void setDate(uint8_t index_day, uint8_t day, uint8_t index_month, uint8_t years) `  
This fonction is use to set the date.  
To set the Date you have to put in order :
The index day like 1 = Monday, 2 = Tuesday, ... ,7 = Sunday.  
The day like 26.
The index month like 1 = January, 2 = February, ... 12 = December.
And the years like 25 for 2025.
> Like the ` setTime() ` I don't have make an auto time set fonction yet.

` uint8_t getYears() `  
This fonction return the year in uint8_t like 23, 24 ,25 etc.
> The fonction doesn't return the thousands because the DS3231 doesn't calculate it.

` uint8_t getHour() `  
This fonction return the Hours in uint8_t like 11, 12, 13 etc.

` uint8_t getMinute() `  
This fonction return the Minutes in uint8_t like 38, 39, 40 etc.

` uint8_t getSecond() `  
This fonction return the Seconds in uint8_t like 57, 58, 59 etc.

` uint8_t getDay() `  
This fonction return the Days in uint8_t like 24, 25, 26 etc.

` String getStringDay() `
This fonction return the Days in String  like Monday, Tuesday, Wednesday etc.
> The language change with which version that you download

` String getStringMonth() `  
This fonction return the Month in String  like Jan = January, Feb = February, Mar = March etc.
> The language change with which version that you download

` String getStringTime() `  
This fonction return the Month in String  like Hours:Minutes:Seconds.  

` String getStringDate() `  
This fonction return the Month in String like Month/Day/Years.
> The order change with which version that you download like in french it's Day/Month/Years

## Thank's for downloading and help me to upgrade my libraries and my skills 👍
