/*   VUASRL 김재은
 *    가변저항 A0에 연결시켜서 가변저항의 값을 SD카드에 기록해보기.
 * 
 */



#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

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
  File dataFile = SD.open("VUASRL.csv", FILE_WRITE);

  if (dataFile) 
  {
                                                                           //unsigned int data = analogRead(A0);
                                                                           //String(data)
                                                                           //string data =string(h)+","+string(t);
    dataFile.println(analogRead(A0));  //여기에 출력되는 값을 적어준다,.
    dataFile.close();
    Serial.println(analogRead(A0));
  }

  else 
  {
    Serial.println("error opening VUASRL.txt");
  }
}
