//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
int servo_speed = 5;
void setup() {

  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);

}

void loop() {
  Serial.println("Start");
//  Dynamixel.moveSpeed(10, dynamixelBeta(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(17, dynamixelAlpha(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(12, dynamixelGamma(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  //Left-Front
//  Dynamixel.moveSpeed(22, dynamixelBeta(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(20, dynamixelAlpha(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  Dynamixel.moveSpeed(9, dynamixelGamma(11.5, 11.5, 4, 0, 0) ,100);
//  delay(10);
//  //Right-Back
//  Dynamixel.moveSpeed(11, dynamixelBeta(11.5, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(18, dynamixelAlpha(11.5, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(1, dynamixelGamma(11.5, 11.5, 4, 1, 0) ,400);
//  delay(10);
//  //Right-Front
////  Dynamixel.moveSpeed(14, AngleCalc(AngleMirror(TibiaAngle(Beta_Calculation(x_val, y_val, z_val), 1))) ,400);
//  Dynamixel.moveSpeed(14, dynamixelBeta(11.5, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(5, dynamixelAlpha(11.5, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(2, dynamixelGamma(11.5, 11.5, 4, 1, 0) ,400);
//  delay(10);

  Berdiri();
  delay(5000);
//  Serial.println("raise left front leg");
//  LeftFront(10, 10, 3);
//  LeftBack(10, 10, 3);
//  RightFront(10.5, 10.5, 4);
//  RightBack(10.5, 10.5, 4);
//  delay(1000);
//  Serial.println("moving left front leg forward");
//  LeftFront(9.5, 10.5, 3);
//  LeftBack(9.5, 10.5, 4);
//  RightFront(10.5, 10.5, 4);
//  RightBack(10.5, 10.5, 4);
//  delay(1000);
//  Serial.println("lower left front leg");
//  LeftFront(9.5, 11, 4);
//  LeftBack(9.5, 11, 4);
//  RightFront(10.5, 10.5, 4);
//  RightBack(10.5, 10.5, 4);
//  delay(1000);
  
  Serial.println("raise leg");
  LeftFront(10, 10, 3);
  LeftBack(10, 10, 3);
  RightFront(10, 10, 3);
  RightBack(10, 10, 3);
  delay(1000);
  Serial.println("movingleg forward");
  LeftFront(9.5, 10.5, 3);
  LeftBack(9.5, 10.5, 3);
  RightFront(9.5, 10.5, 3);
  RightBack(9.5, 10.5, 3);
  delay(1000);
  Serial.println("lower leg");
  LeftFront(9.5, 11, 4);
  LeftBack(9.5, 11, 4);
  RightFront(9.5, 11, 4);
  RightBack(9.5, 11, 4);
  delay(1000);
  
//  Dynamixel.moveSpeed(14, dynamixelBeta(10, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(5, dynamixelAlpha(10, 11.5, 4, 1, 1) ,400);
//  delay(10);
//  Dynamixel.moveSpeed(2, dynamixelGamma(10, 11.5, 4, 1, 0) ,400);
//  delay(10);
  

  
//
//  Serial.println("--------------------------------------------------------------------");
//  Berdiri(10, 11.5, 4);
//  Serial.println("--------------------------------------------------------------------");
  delay(1000);
  
}
