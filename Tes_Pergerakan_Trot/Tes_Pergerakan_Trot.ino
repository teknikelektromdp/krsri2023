//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
    
int servo_delay = 1;
int servo_speed = 850;

void setup() {
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int starting_x=8, starting_z=4,
      desired_x=5,  desired_z=1,
      delay_servo=1;
  double increment=0.6, decrement=0.6;
  Serial.println("Start");
  Berdiri();//x_val=y_val=8; z_val=3
  delay(2000);

//  while(1){
////    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-decrement, j=j-decrement){
////      RightFront(i,8,j);
////      LeftBack(i,8,j);
////      delay(delay_servo); 
////    }
////    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z; i=i+increment, j=j+increment){
////      RightFront(i,8,j);
////      LeftBack(i,8,j);
////      delay(delay_servo);
////    }
////
////    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-decrement, j=j-decrement){
////      LeftFront(i,8,j);
////      RightBack(i,8,j);
////      delay(delay_servo);
////    }
////    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z;i=i+increment, j=j+increment){
////      LeftFront(i,8,j);
////      RightBack(i,8,j);
////      delay(delay_servo);
////    }
//
//  
//  }
while(1){
  trajectoryPlanningMirror(5,30,2,3,3,4);
  delay(10);
  Serial.println("-------------------------------------------------------------");
  trajectoryPlanning(5,30,2,3,3,4);
  delay(10);
}
}

void trajectoryPlanning(int x0,float t,int deltaT,int AEPx,int fc,int z0)
{
  int step_=t/deltaT;
  float x0_=x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++)
  {
    if(i==0)
    {
      x=x0;
      z=z0;      
    }
    else
    {
      x=x0_+((x0+AEPx-x0_)/deltaT);
      z=z0;
    }
    Serial.print("x");
    Serial.println(i);
    Serial.println(x);
    Serial.print("z: ");
    Serial.println(z);
    LeftFront(x,8,z);
    x0_=x;
    z0_=z;    
//    delay(00);
  }
}

void trajectoryPlanningMirror(int x0,float t,int deltaT,float AEPx,int fc,int z0)
{
  int step_=t/deltaT;
  float x0_=AEPx+x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++)
  {
    if(i==0)
    {
      x=AEPx+x0;
      z=z0;      
    }
    else
    {
      x=x0_+(((AEPx+x0)+(AEPx*-1)-x0_)/deltaT);    
      z=fc*sin(Degree_to_Rad(180*((((i+1)*2)-t)/t)))+z0;
    }
    Serial.print("x");
    Serial.println(i);
    Serial.println(x);
    Serial.print("z: ");
    Serial.println(z);
    LeftFront(x,8,z);
    x0_=x;
    z0_=z;    
  }
}
