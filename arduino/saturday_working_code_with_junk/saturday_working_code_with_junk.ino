#include <SoftwareSerial.h>


SoftwareSerial GPS = SoftwareSerial(0,1);

void setup(){
  GPS.begin(4800);
  Serial.begin(9600);
  
  Serial.println("Hello Harry!");
}

void loop(){
  byte reading = GPS.read();
  Serial.write(reading);
  delay(2000);
//    Serial.println("asdf")
}
