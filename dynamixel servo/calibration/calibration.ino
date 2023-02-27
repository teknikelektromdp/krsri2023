#include <DynamixelSerial.h>
/*
 * 26 = RBT = Right Back Top ok
 * 28 = RBB = Right Back Bottom ok
 * 24 = RFT = Right Front Top ok
 * 14 = RFB = Right Front Bottom ok
 * 21 = LBT = Left Back Top ok
 * 18 = LBB = Left Back Bottom ok
 * 5 = LFT = Left Front Top ok
 * 9 = LFB = Left Front Bottom ok
 */ 
void setup(){
Dynamixel.setSerial(&Serial3); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
Dynamixel.begin(1000000,2);  // Initialize the servo at 1 Mbps and Pin Control 2
delay(1000);
}

void loop(){
  Dynamixel.move(24,map(150, 0, 300, 0, 1000));
  Dynamixel.move(26,map(150, 0, 300, 0, 1000));
  Dynamixel.move(28,map(150, 0, 300, 0, 1000));
  Dynamixel.move(14,map(150, 0, 300, 0, 1000));
  Dynamixel.move(18,map(150, 0, 300, 0, 1000));
  Dynamixel.move(5,map(150, 0, 300, 0, 1000));
  Dynamixel.move(9,map(150, 0, 300, 0, 1000));
  Dynamixel.move(21,map(150, 0, 300, 0, 1000));
  delay(1000);
}
