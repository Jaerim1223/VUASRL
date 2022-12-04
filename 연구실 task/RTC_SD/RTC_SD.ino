/* VUSARL 김재은
 *  RTC, SD카드 연동 
 *  
 *  
 *
 */
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include <Wire.h>
#include <stdio.h>

const int chipSelect = 4;
// mosi 11, sck13, miso 12
RTC_DS1307 rtc;
int sec = 0;
int min = 0;
int counter = 0;

String string1 = "VUASRL.csv";
String string2 = "__TIME__";

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
      

    
   File dataFile = SD.open(string1 + string2 , FILE_WRITE);
    dataFile.print("Trust\t");
    dataFile.println("Time");
    dataFile.close();

  if (! rtc.begin()) 
  {
    Serial.print("Couldn't fine RTC");
    while (1);
  }

  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running, let's set the time!");
  }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     

}
   
void loop() {
  sec = millis()/1000-60*counter;
  if(sec == 60) { counter++;min++;}
  
  File dataFile = SD.open(string1 + string2, FILE_WRITE);  //csv하면 엑셀 txt하면 메모장
  DateTime now = rtc.now();
  
  if (dataFile) 
  {
                                                                          
                                                                           //unsigned int data = analogRead(A0);
                                                                           //String(data)
    dataFile.print("\n");                                                                       //string data =string(h)+","+string(t);
    dataFile.print(analogRead(A0));  
    dataFile.print("\t");                      //여기에 출력되는 값을 적어준다,.
    dataFile.print(min);
    dataFile.print(':');
    dataFile.print(sec);
    
    
    dataFile.close();
    Serial.println(analogRead(A0));
  }

  else 
  {
    Serial.println("error opening VUASRL.csv");
  }
  

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    delay(1000);
    

}
