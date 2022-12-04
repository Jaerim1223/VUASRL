/* 
 *  VUSARL 김재은
 *  SD카드와 RTC 모듈 S/W 통합 
 *  SD카드에 업로드할때마다 시간값을 붙혀 파일을 생성시킴.(분 당)
 *  저장된 txt파일에 A0(가변저항값 이 코드에는 연결안됨)와 스톱워치의 형태의 시간으로 저장
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

String MyString;
String Parameter1= "VUASRL"; 
unsigned char Parameter2;
String Parameter3 = ".csv";


void setup() {
 Serial.begin(9600);
 Serial.print("SD 초기화..");
 
 SD.begin(chipSelect) ; 
 
   rtc.begin();

   DateTime now = rtc.now();

   unsigned char Parameter2 = now.minute();
   
   MyString = Parameter1 + Parameter2 + Parameter3;
  
   File dataFile = SD.open(MyString, FILE_WRITE);

    dataFile.print(__TIME__);
    dataFile.println();
    dataFile.print("Trust\t");
    dataFile.print("RPM\t");
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
  
                   
  sec = millis()/1000-60*counter;
  if(sec == 60) { counter++;min++;}   
  
  File dataFile = SD.open(MyString, FILE_WRITE);  //csv하면 엑셀 txt하면 메모장
  
  if (dataFile) 
  {
    dataFile.print(analogRead(A0)); // RPM값 넣으세요
    dataFile.print("\t");
    dataFile.print(analogRead(A1));  
    dataFile.print("\t");                      //여기에 출력되는 값을 적어준다,.
    dataFile.print(min);
    dataFile.print(':');
    dataFile.print(sec);
    dataFile.println();
    
    dataFile.close();
    Serial.println();
    Serial.print("Trust");
    Serial.print("\t");
    Serial.println("RPM");
    Serial.print(analogRead(A0));
    Serial.print("\t");
    Serial.println(analogRead(A1));
 
  }

  else 
  {
    Serial.println("error opening VUASRL.csv");
  }
  

    Serial.print(min);
    Serial.print("분");
    Serial.print(sec);
    Serial.print("초");
    Serial.println();

    delay (1000);

}
