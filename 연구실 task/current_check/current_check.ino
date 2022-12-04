int value;
float amp;   //암페어줄인

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);

}

void loop() {
  value = analogRead(A0);
  amp = (((value-510)*5/0.185)/1024)*1000;; //515는 초기전압값 평균낸거 이후 x5/1024를 해줘서 전압값으로 변경해줌.
  Serial.println(amp);
  delay(250);
  
}
