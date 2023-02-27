#include <DynamixelSerial.h>
int id = 0;

int findId()
{
  while(Dynamixel.ping(id) != 0)
  {
    id++;
  }
  return id;
}
void setup(){
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial3); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,2);  // Initialize the servo at 1 Mbps and Pin Control 2
  delay(1000);
}
void loop(){
  Serial.println("Scanning the servo, please wait...");
  if(findId() > 0)
  {
    Serial.print("ID : ");
    Serial.println(findId()); 
  }
  else
  {
    Serial.println("Cannot get response from servo motor");
  }
  delay(1000);
}
