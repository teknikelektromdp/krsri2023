//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;

void setup() {

  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);

}

void loop() {
  //Standing Limit
  //Left-Back
//  Dynamixel.moveSpeed(10, AngleCalc(165) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(17, AngleCalc(130) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(12, AngleCalc(30) ,100);
//  delay(10);
//  //Left-Front
//  Dynamixel.moveSpeed(22, AngleCalc(165) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(20, AngleCalc(130) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(9, AngleCalc(30) ,100);
//  delay(10);
//  //Right-Back
//  Dynamixel.moveSpeed(11, AngleCalc(AngleMirror(165)) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(18, AngleCalc(AngleMirror(130)) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(1, AngleCalc(30) ,400);
//  delay(10);
//  //Right-Front
//  Dynamixel.moveSpeed(14, AngleCalc(AngleMirror(181)) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(5, AngleCalc(AngleMirror(163)) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(2, AngleCalc(34) ,400);
//  delay(10);
//
//  delay(5000);
  Serial.println("--------------------------------------------------------------------");
  Berdiri(10, 11.5, 4);
  Serial.println("--------------------------------------------------------------------");
  delay(1000000000);
}
