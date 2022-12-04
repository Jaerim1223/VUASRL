/* VUSARL 김재은
 *  가변저항을 A0에 연결해서 가변저항의 값과 RTC의 값을 I2C LCD로 출력하면
 *  출력된 값을 SD카드에 만들어진 파일에 저장하기.
 *
 */
#include <SPI.h>
#include <SD.h>
#include <stdio.h>

const int chipSelect = 4;
// mosi 11, sck13, miso 12


void setup() {
 Serial.begin(9600);

 Serial.print("Initializing SD card..");           //SD카드 인식
     if (!SD.begin(chipSelect))  
     {
      Serial.println("Card failed. or not present");
      while  (1);
     }
      Serial.println("Card initialized.");
      
}
void loop() {
  File dataFile = SD.open("VUASRL.csv", FILE_WRITE);  //csv하면 엑셀 txt하면 메모장
  
  if (dataFile) 
  {
                                                                          
                                                                           //unsigned int data = analogRead(A0);
                                                                           //String(data)
                                                                           //string data =string(h)+","+string(t);
    dataFile.println(analogRead(A0));  //가변저항값 쓰기
    dataFile.println(__TIME__);           //RTC값 쓰기
    dataFile.close();
  }

  else 
  {
    Serial.println("error opening VUASRL.csv");
  }
  
  

}
