 #include "HX711.h"
#include <Wire.h>


HX711 scale;
 
float calibration_factor =( input your loadcell factor);

int weight;

void setup() {

 Serial.begin(38400);
 scale.begin(2, 3);  // first HX711 DTpin, second HX711 SCKpin

 scale.set_scale();
 scale.tare(); //Reset the scale to 0



 }




void loop() {
 scale.set_scale(calibration_factor);

 Serial.print("weight :\t");
 Serial.print(scale.get_units() * 0.453592, 2);   //first = Unit conversion (lb to kg), second = decimal point
 Serial.println(" kg");

 
 delay(1000);
 }
