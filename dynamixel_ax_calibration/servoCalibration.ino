#include <DynamixelSerial.h>

void setup(){
  Dynamixel.setSerial(&Serial2); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,15);  // Initialize the servo at 1 Mbps and Pin Control 2
  delay(1000);
  Serial.begin(9600);
}

void loop(){
  //don't map the value of position
  //0 = 0 degree 
  //500 = 150 degree
  //1023 = 300 degree
  
  //ID 10 = 150 degree (bottom)
  //ID 17 = 150 degree (middle)
  //ID 12 = 30 degree (top)

  //ID 11 = 150 degree (bottom)
  //ID 18 = 150 degree (middle)
  //ID 1 = 30 degree (top)

  //ID 14 = 150 degree (bottom)
  //ID 17 = 150 degree (middle)
  //ID 2 = 30 degree (top)

  //ID 22 = 150 degree (bottom)
  //ID 20 = 150 degree (bottom)
  //ID 9 = 30 degree (bottom) 
  
  Dynamixel.moveSpeed(22, angleCalculation(150) ,400);
//    Serial.println(Dynamixel.setID(17, 5));
  delay(1000);
}

int angleCalculation(float angle)
{
  float angle_calc = (angle/300)*1023;
  return angle_calc;
}
