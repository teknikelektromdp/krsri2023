//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
    
int servo_delay = 1;
int servo_speed = 1000;

void setup() {
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int starting_x=8/*last working value(=8)*/, starting_z=9,//last try(=4)
      desired_x=5/*last working value(=5)*/,  desired_z=4,//last try(=1)
      starting_y=8/*last try(=8)*/, test_desired_y=5,//only for testing, since when using 5 for x value it only make the robot move backward
      delay_servo=1;
  double  x_increment=(double)(starting_x-desired_x)/3,
          z_increment=(double)(starting_z-desired_z)/5;
  Serial.println("Start");
  Berdiri();//x_val=y_val=8; z_val=3
  delay(2000);
  Serial.print("X increment");
  Serial.println(x_increment);
  Serial.print("z increment");
  Serial.println(z_increment);


//without making sine-like movement value on z parameter
//while(1){
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      RightFront(i,8,desired_z);
//      LeftBack(i,8,desired_z);
//      delay(delay_servo); 
//    }
//    
//    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z; i=i+x_increment, j=j+z_increment){
//      RightFront(i,8,j);
//      LeftBack(i,8,j);
//      delay(delay_servo);
//    }
//
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      LeftFront(i,8,desired_z);
//      RightBack(i,8,desired_z);
//      delay(delay_servo);
//    }
//    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z;i=i+x_increment, j=j+z_increment){
//      LeftFront(i,8,j);
//      RightBack(i,8,j);
//      delay(delay_servo);
//    }
//  }
  /*
   * //making z value on robot movement increase and decrease like sine signal
  while(1){
    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-x_increment, j=j-z_increment){
      RightFront(i,8,j);
      LeftBack(i,8,j);
      delay(delay_servo); 
    }
    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z; i=i+x_increment, j=j+z_increment){
      RightFront(i,8,j);
      LeftBack(i,8,j);
      delay(delay_servo);
    }

    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-x_increment, j=j-z_increment){
      LeftFront(i,8,j);
      RightBack(i,8,j);
      delay(delay_servo);
    }
    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z;i=i+x_increment, j=j+z_increment){
      LeftFront(i,8,j);
      RightBack(i,8,j);
      delay(delay_servo);
    }
  }
  */
//  //attempt to moving the legs simultanuously while the other is moving
//  //test result = success, but robot moving backward no matter what the order of sequence
//  while(1){
//    //setting up first move
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      RightFront(i,8,desired_z);
//      LeftBack(i,8,desired_z);
//      delay(delay_servo); 
//    }
//    while(1){
//      for(double  i=desired_x, j=desired_z, n=starting_x; 
//                  i<=starting_x, j<=starting_z, n>=desired_x;
//                  i=i+x_increment, j=j+z_increment, n=n-desired_x){
//        RightFront(i,8,j);
//        LeftBack(i,8,j);
//        LeftFront(n,8,desired_z);
//        RightBack(n,8,desired_z);
//        delay(delay_servo);
//      }
//      for(double  i=desired_x, j=desired_z, n=starting_x;
//                  i<=starting_x, j<=starting_z, n>=desired_x;
//                  i=i+x_increment, j=j+z_increment, n=n-desired_x){
//        LeftFront(i,8,j);
//        RightBack(i,8,j);
//        RightFront(n,8,desired_z);
//        LeftBack(n,8,desired_z);
//        delay(delay_servo);
//      }
//    }
//  }
  
  //attempt to moving the legs simultanuously while the other is moving
  //test result = 
  while(1){
    //setting up first move
    for(double i=starting_y; i>=test_desired_y; i=i-x_increment){
      RightFront(8, i, desired_z);
      LeftBack(8,i, desired_z);
      delay(delay_servo); 
    }
    while(1){
      for(double  i=test_desired_y, j=desired_z, n=starting_y; 
                  i<=starting_y, j<=starting_z, n>=test_desired_y;
                  i=i+x_increment, j=j+z_increment, n=n-test_desired_y){
        RightFront(8,i,j);
        LeftBack(8,i,j);
        LeftFront(8,n,desired_z);
        RightBack(8,n,desired_z);
        delay(delay_servo);
      }
      for(double  i=test_desired_y, j=desired_z, n=starting_y;
                  i<=starting_x, j<=starting_z, n>=test_desired_y;
                  i=i+x_increment, j=j+z_increment, n=n-test_desired_y){
        LeftFront(8,i,j);
        RightBack(8,i,j);
        RightFront(8,n,desired_z);
        LeftBack(8,n,desired_z);
        delay(delay_servo);
      }
    }
  }
//  while(1){
//    trajectoryPlanningMirrorB(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanningB(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanningMirror(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanning(6,20,2,3,3,4);
//    delay(10);
//  }
}
