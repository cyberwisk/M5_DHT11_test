/**
 * @file M5_TDH11_test.ino
 * @author Aurélio Avanzi
 * @brief M5StickCPlus DHT11_test
 * @version 0.1
 * @date 2023-12-12
 *
 * @Hardwares: M5Cardputer
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 */

#include "M5StickCPlus.h"
#include "AXP192.h"
#include "DHT.h"

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

#define DHTPIN 26 // what pin we're connected to
#define TFT_GREY 0x5AEB
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
M5.begin();
M5.Lcd.setRotation(0);
dht.begin();

    RTC_TimeTypeDef TimeStruct;
    TimeStruct.Hours   = 11;  // Set the time. 
    TimeStruct.Minutes = 20;
    TimeStruct.Seconds = 00;
    //M5.Rtc.SetTime(&TimeStruct);  // writes the set time to the real time clock.

    RTC_DateTypeDef DateStruct;
    DateStruct.WeekDay = 1;  // Set the date.
    DateStruct.Month   = 12;
    DateStruct.Date    = 04;
    DateStruct.Year    = 2023;
    //M5.Rtc.SetDate(&DateStruct);  // writes the set date to the real time clock.
}

void loop() {

// Wait a few seconds between measurements.
delay(1000);
M5.Lcd.fillScreen(TFT_BLACK);
// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
float h = dht.readHumidity();
// Read temperature as Celsius
float t = dht.readTemperature();
// Read temperature as Fahrenheit
float f = dht.readTemperature(true);

M5.Lcd.setCursor(0, 0, 2);
M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
M5.Lcd.setTextSize(1);
M5.Lcd.print(" DHT11 Temp/Humid ");
M5.Lcd.println("");
// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
  M5.Lcd.setTextColor(TFT_RED,TFT_BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println(" ---------");
  M5.Lcd.println("NO DHT11");
  M5.Lcd.println("  in G26  ");
  M5.Lcd.println(" ---------");
return;
}
// Compute heat index
// Must send in temp in Fahrenheit!
float hi = dht.computeHeatIndex(f, h);
M5.Lcd.println("");
M5.Lcd.println(" Humidity: ");
M5.Lcd.setTextSize(2);
M5.Lcd.print(" ");
M5.Lcd.println(h);
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(TFT_YELLOW,TFT_BLACK);
M5.Lcd.println(" Temperature: ");
M5.Lcd.setTextColor(TFT_RED,TFT_BLACK);
M5.Lcd.setTextSize(2);
M5.Lcd.print(" ");
M5.Lcd.print(t);
M5.Lcd.println("c");
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(TFT_GREEN,TFT_BLACK);
//M5.Lcd.print(" Heat index: ");
//M5.Lcd.println(hi);

M5.Rtc.GetTime(&RTC_TimeStruct);  // Gets the time in the real-time clock.
M5.Rtc.GetDate(&RTC_DateStruct);
    
M5.Lcd.printf(" Data : %04d-%02d-%02d\n", RTC_DateStruct.Year,RTC_DateStruct.Month, RTC_DateStruct.Date);
M5.Lcd.printf(" Time : %02d : %02d : %02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
M5.Lcd.setTextColor(TFT_PINK,TFT_BLACK);
M5.Lcd.println(" Battery by AXP192");
M5.Lcd.printf(" V: %.3fv\r\n",M5.Axp.GetBatVoltage());
M5.Lcd.printf(" I: %.3fma\r\n",M5.Axp.GetBatCurrent());
M5.Lcd.setTextColor(TFT_GREY,TFT_BLACK);
M5.Lcd.printf(" AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());

}
