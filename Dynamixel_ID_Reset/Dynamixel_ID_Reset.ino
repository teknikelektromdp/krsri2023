#include<DynamixelSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial2); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,5);  // Inicialize the servo at 1 Mbps and Pin Control 5
  delay(1000);
  Dynamixel.setID(17,7);
  Serial.print("Done Resetting");
}

void loop() {
  // put your main code here, to run repeatedly:

}
