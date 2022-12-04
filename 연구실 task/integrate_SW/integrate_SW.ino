/* VUSARL 김재은
 *  가변저항을 A0에 연결해서 가변저항의 값과 RTC의 값을 I2C LCD로 출력하면
 *  출력된 값을 SD카드에 만들어진 파일에 저장하기.
 *
 */
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdio.h>서

const int chipSelect = 4;
// mosi 11, sck13, miso 12
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
 Serial.begin(9600);

 Serial.print("Initializing SD card..");           //SD카드 인식
     if (!SD.begin(chipSelect))  
     {
      Serial.println("Card failed. or not present");
      while  (1);
     }
      Serial.println("Card initialized.");
      
  lcd.begin ();
  lcd.backlight();
  lcd.println("VUASRL");
  delay(5000);


  if (! rtc.begin()) 
  {
    lcd.print("Couldn't fine RTC");
    while (1);
  }

  if (! rtc.isrunning())
  {
    lcd.println("RTC is NOT running, let's set the time!");
  }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     

}

void loop() {
  File dataFile = SD.open("VUASRL.csv", FILE_WRITE);  //csv하면 엑셀 txt하면 메모장
  DateTime now = rtc.now();
  if (dataFile) 
  {
                                                                          
                                                                           //unsigned int data = analogRead(A0);
                                                                           //String(data)
                                                                           //string data =string(h)+","+string(t);
    dataFile.println(analogRead(A0));//여기에 출력되는 값을 적어준다,.
    dataFile.println(__TIME__);
    dataFile.close();
    Serial.println(analogRead(A0));
  }

  else 
  {
    Serial.println("error opening VUASRL.csv");
  }
  
     lcd.setCursor(0, 0);
    lcd.print("TIME");
    lcd.print(" ");
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    lcd.print(" ");
    
    unsigned int data = analogRead(A0);
    lcd.setCursor(0, 1);
    lcd.print("Thrust");
    lcd.print(':');
    lcd.print(String(data));
    

     Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    delay(1000);
    

}
