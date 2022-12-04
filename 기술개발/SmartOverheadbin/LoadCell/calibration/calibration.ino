/* VUASRL KimjaeEun
 * loadcell calibration code.
 */
#include "HX711.h"



const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;        //DT pin, SCK pin location 

HX711 scale;

void setup() {
  Serial.begin(38400);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale();                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("5초안에 1.25kg짜리 물건을 올려두세요!");
  delay(5000);
  Serial.println(scale.get_units());  //lb to kg
  float factor = -7000;  // default value 7000

  while(true){  
    scale.set_scale(factor);
     float weight = (scale.get_units()*453.592, 3);
    Serial.println(weight);
    //weight == 500g code stop.
    if(weight <= 1200){
      break;
    }else{
      factor += 10 ;//   if(Serial fast finish) --> factor value down . ex) 100 -> 10
    }
  }
  Serial.print("modification value = ");
  Serial.println(factor);
}            
void loop() {
  // put your main code here, to run repeatedly:
}
