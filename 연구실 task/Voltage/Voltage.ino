
void setup() {
 Serial.begin(9600);

}

void loop() {
   float V_ADC = analogRead(A0);
   float V = V_ADC * 5.0 / 1024.0 / 0.2;
   Serial.print("전압: ");
   Serial.print(V);
   Serial.println(" V");
   delay(1000);
}
