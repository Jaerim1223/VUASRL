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





void setup() {
 Serial.begin(9600);

 SD.begin(chipSelect) ; 

  
   File dataFile = SD.open("VUASRL.csv", FILE_WRITE);

    dataFile.println();
    dataFile.print("Trust\t");
    dataFile.println("Time");
    dataFile.println();
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
  
  
  File dataFile = SD.open("VUASRL.csv", FILE_WRITE);  //csv하면 엑셀 txt하면 메모장
  DateTime now = rtc.now();
   sec = millis()/1000-60*counter;
   if(sec == 60) { counter++;min++;}
   
  if (dataFile) 
  {
                                
                                                                           //unsigned int data = analogRead(A0);
                                                                           //String(data)                                                                       //string data =string(h)+","+string(t);
    dataFile.print(analogRead(A0));  
    dataFile.print("\t");                      //여기에 출력되는 값을 적어준다,.
    dataFile.print(min);
    dataFile.print(':');
    dataFile.print(sec);
    dataFile.println();
    
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
