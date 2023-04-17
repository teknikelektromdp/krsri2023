//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
    
int servo_delay = 1;
int servo_speed = 700;
void setup() {

  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);

}

void loop() {
  Serial.println("Start");
//  LeftFront(12.5, 12.5, 3);
//  LeftBack(12.5, 12.5, 3);
//  RightFront(12.5, 12.5, 3);
//  RightBack(12.5, 12.5, 3);
//  Dynamixel.moveSpeed(11, dynamixelBeta(12.5, 12.5, 3, 1, 1) ,servo_speed);
//  delay(servo_delay);
//  Dynamixel.moveSpeed(18, dynamixelAlpha(12.5, 12.5, 3, 0, 1) ,servo_speed);
//  delay(servo_delay);
//  Dynamixel.moveSpeed(1, dynamixelGamma(12.5, 12.5, 3, 0, 0) ,servo_speed);
//  delay(servo_delay);
//  delay(2000);
//  Dynamixel.moveSpeed(11, dynamixelBeta(12.5, 12.5, 3, 1, 1) ,servo_speed);
//  delay(servo_delay);
//  Dynamixel.moveSpeed(18, dynamixelAlpha(12.5, 12.5, 3, 0, 1) ,servo_speed);
//  delay(servo_delay);
//  Dynamixel.moveSpeed(1, dynamixelGamma(12.5, 12.5, 3, 1, 0) ,servo_speed);
//  delay(servo_delay);
  delay(2000);
//


//  LeftFront(7,7,3);
//  LeftBack(7, 12.5, 3);
//  RightFront(12.5, 12.5, 3);
//  RightBack(12.5, 12.5, 3);
//delay(30000000);

  Berdiri();//x_val=y_val=7; z_val=3
//
////  delay(1000000000);
//  //preparation step
//  Serial.println("Prep");
////  LeftFront(7, 7, 4);
//
//  LeftBack(3.8, 9.1, 3);
//  RightFront(3.8, 9.1, 3);
////  RightBack(7, 7, 4);
//
//  delay(1000000000000000);
//
// LeftFront(10, 10, 3);
/*
 * 
*/    
      LeftFront(8, 8, 4);
      LeftBack(9, 7, 4);
      RightFront(9, 7, 4);
      RightBack(8, 8, 4);
      delay(100);
  while(1){
      //first step
      Serial.println("First step");
      //Raising right back up
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 3);
    //  RightFront(8, 6, 3);
      RightBack(9, 9, 1);
      delay(100);
      
      //moving right back forward
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 4);
    //  RightFront(8, 6, 4);
      RightBack(5.5, 9.5, 1);
      delay(100);
  
      //dropping right back down
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 4);
    //  RightFront(8, 6, 4);
      RightBack(3.5, 8.5, 4);
      delay(100);
   
       //raising right front up
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 4);
      RightFront(9, 7.5, 1);
    //  RightBack(5.5, 7.5, 3);
      delay(50);
      //moving right front forward
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 4);
      RightFront(6.5, 8.5, 1);
    //  RightBack(5.5, 7.5, 4);
      delay(50);
      //dropping right front down
    //  LeftFront(7, 7, 4);
    //  LeftBack(8, 6, 4);
      RightFront(6.5, 8.5, 4);
    //  RightBack(5.5, 7.5, 4);
    //  delay(10);
    
      
      delay(100);
      Serial.println("Second step");
      //moving right back, right front, and left front back
      RightFront(8, 8, 4);
      LeftFront(9, 6, 4);
    //  LeftBack(8, 6, 4);
      RightBack(9, 6, 4);
      delay(100);
    
    
      Serial.println("Third step");
      //Raising right back up
    //  RightFront(10.5, 10.5, 4);
      RightBack(9, 7, 4);
      LeftFront(9, 7, 4);
      LeftBack(9, 9, 1);
      delay(50);
      //moving right back forward
    //  RightFront(7, 7, 4);
    //  RightBack(8, 6, 4);
    //  LeftFront(8, 6, 4);
      LeftBack(6.5, 8.5, 1);
      delay(50);
      //dropping right back down
    //  RightFront(7, 7, 4);
    //  RightBack(8, 6, 4);
    //  LeftFront(8, 6, 4);
      LeftBack(6.5, 8.5, 4);
      delay(50);
      //raising right front up
    //  RightFront(7, 7, 4);
    //  RightBack(8, 6, 4);
      LeftFront(9, 7.5, 1);
    //  LeftBack(5.5, 7.5, 3);
      delay(50);
      //moving right front forward
    //  RightFront(7, 7, 4);
    //  RightBack(8, 6, 4);
      LeftFront(6.5, 8.5, 1);
    //  LeftBack(5.5, 7.5, 4);
      delay(50);
      //dropping right front down
    //  RightFront(7, 7, 4);
    //  RightBack(8, 6, 4);
      LeftFront(6.5, 8.5, 4);
    //  LeftBack(5.5, 7.5, 4);
    //  delay(10);
    
      
      delay(100);
      Serial.println("Forth step");
      //moving right back, right front, and left front back
      LeftFront(8, 8, 4);
      RightFront(9, 6, 4);
    //  LeftBack(8, 6, 4);
      LeftBack(9, 6, 4);
      delay(50);
    //  delay(1000);
    //  Serial.println("lower left front leg");
    //  LeftFront(6, 7.5, 4);
    //  LeftBack(6, 7.5, 4);
    //  RightFront(7, 7, 4);
    //  RightBack(7, 7, 4);
      delay(100);
  }
//  while(1){
//      //first step
//      Serial.println("First step");
//      //Raising right back up
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 3);
//    //  RightFront(8, 6, 3);
//      RightBack(8, 8, 1);
//      delay(100);
//      
//      //moving right back forward
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 4);
//    //  RightFront(8, 6, 4);
//      RightBack(4.5, 8.5, 1);
//      delay(100);
//  
//      //dropping right back down
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 4);
//    //  RightFront(8, 6, 4);
//      RightBack(2.5, 7.5, 3);
//      delay(100);
//   
//       //raising right front up
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 4);
//      RightFront(8, 6.5, 1);
//    //  RightBack(5.5, 7.5, 3);
//      delay(50);
//      //moving right front forward
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 4);
//      RightFront(5.5, 7.5, 1);
//    //  RightBack(5.5, 7.5, 4);
//      delay(50);
//      //dropping right front down
//    //  LeftFront(7, 7, 4);
//    //  LeftBack(8, 6, 4);
//      RightFront(5.5, 7.5, 3);
//    //  RightBack(5.5, 7.5, 4);
//    //  delay(10);
//    
//      
//      delay(100);
//      Serial.println("Second step");
//      //moving right back, right front, and left front back
//      RightFront(7, 7, 3);
//      LeftFront(8, 5, 3);
//    //  LeftBack(8, 6, 4);
//      RightBack(8, 5, 3);
//      delay(100);
//    
//    
//      Serial.println("Third step");
//      //Raising right back up
//    //  RightFront(10.5, 10.5, 4);
//      RightBack(8, 6, 3);
//      LeftFront(8, 6, 3);
//      LeftBack(8, 8, 1);
//      delay(50);
//      //moving right back forward
//    //  RightFront(7, 7, 4);
//    //  RightBack(8, 6, 4);
//    //  LeftFront(8, 6, 4);
//      LeftBack(5.5, 7.5, 1);
//      delay(50);
//      //dropping right back down
//    //  RightFront(7, 7, 4);
//    //  RightBack(8, 6, 4);
//    //  LeftFront(8, 6, 4);
//      LeftBack(5.5, 7.5, 3);
//      delay(50);
//      //raising right front up
//    //  RightFront(7, 7, 4);
//    //  RightBack(8, 6, 4);
//      LeftFront(8, 6.5, 1);
//    //  LeftBack(5.5, 7.5, 3);
//      delay(50);
//      //moving right front forward
//    //  RightFront(7, 7, 4);
//    //  RightBack(8, 6, 4);
//      LeftFront(5.5, 7.5, 1);
//    //  LeftBack(5.5, 7.5, 4);
//      delay(50);
//      //dropping right front down
//    //  RightFront(7, 7, 4);
//    //  RightBack(8, 6, 4);
//      LeftFront(5.5, 7.5, 3);
//    //  LeftBack(5.5, 7.5, 4);
//    //  delay(10);
//    
//      
//      delay(100);
//      Serial.println("Forth step");
//      //moving right back, right front, and left front back
//      LeftFront(7, 7, 3);
//      RightFront(8, 5, 3);
//    //  LeftBack(8, 6, 4);
//      LeftBack(8, 5, 3);
//      delay(50);
//    //  delay(1000);
//    //  Serial.println("lower left front leg");
//    //  LeftFront(6, 7.5, 4);
//    //  LeftBack(6, 7.5, 4);
//    //  RightFront(7, 7, 4);
//    //  RightBack(7, 7, 4);
//      delay(100);
//  }




//-------------Example-------------
//  LeftFront(12.5, 12.5, 3);
//  RightBack(12.5, 12.5, 3);
//  delay(3000);
//  LeftFront(12.5, 8, 3);
//  RightBack(12.5, 8, 3);
  delay(3000);
  

//  Serial.println("--------------------------------------------------------------------");
//  Berdiri(10, 11.5, 4);
//  Serial.println("--------------------------------------------------------------------");
//  delay(100000);
  
}
