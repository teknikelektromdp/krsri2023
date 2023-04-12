#include <DynamixelSerial.h>

//define the length of each leg
double coxa=6.5, femur=4.7, tibia=6;
//limit the coordinates of leg movement
double x_limit=11.5, y_limit=11.5, z_limit=4;
//value of selected coordinates
double x_val=11.5, y_val=11.5, z_val=4;

//function for converting radian value to degree
double Rad_to_Degree(double Rad){
  double degree = Rad*57.295779513;
  return degree;
}

//function for converting degree value to radian
double Degree_to_Rad(double Degree){
  double rad = Degree*0.01745329252;
  return rad;
}

//inverse kinematics calculation for coxa servo
int Gamma_Calculation(double x, double y, double z){
  double gamma;
  gamma = Rad_to_Degree(atan(x/y));
  //rounding gamma value
  gamma = round(gamma);
  
  return gamma;
}

//inverse kinematics calculation for tibia servo
int Beta_Calculation(double x, double y, double z){
  double L1, beta, L;
  L1 =sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-coxa), 2) + pow(z, 2));
  beta = Rad_to_Degree(acos((pow(tibia, 2) + pow(femur, 2) - pow(L, 2))/(2*tibia*femur)));
  //rounding beta value
  beta = round(beta);
  
  return beta;
}

//inverse kinematics calculation for femur servo
int TotalAlpha_Calculation(double x, double y, double z){
  double L1, L, alpha1, alpha2, alpha_total;
  L1 = sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-coxa), 2) + pow(z, 2));
  alpha1 = Rad_to_Degree(acos(z/L));
  alpha2 = Rad_to_Degree(acos((pow(femur, 2) + pow(L,2) - pow(tibia, 2))/(2*femur*L)));
  alpha_total = alpha1 + alpha2;
  //rounding alpha value
  alpha_total = round(alpha_total);

  return alpha_total;
}
 
//convert an angle to adc value
int aCalc(float angle, int mirror)
{
  float angle_calc=(angle/300)*1023;
  if(mirror == 1)
  {
    int mirror_angle = (angle_calc - 511)*-1;
    mirror_angle += 511;
    return mirror_angle;  
  }
  else
  {
    return angle_calc;
  }
}

int dynamixelAlpha(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_alpha = TotalAlpha_Calculation(x_limit,y_limit,z_limit)-TotalAlpha_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
    return aCalc(130+(dynamixel_alpha*-1),mirror_dynamixel);
  }
  else
  {
    return aCalc(130+dynamixel_alpha,mirror_dynamixel);
  }
}

int dynamixelBeta(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_beta = Beta_Calculation(x_limit,y_limit,z_limit)-Beta_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
     return aCalc(165+(dynamixel_beta*-1),mirror_dynamixel);
  }
  else
  {
    return aCalc(165+dynamixel_beta,mirror_dynamixel);
  }
}

int dynamixelGamma(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_gamma = Gamma_Calculation(x_limit,y_limit,z_limit)-Gamma_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
    return aCalc(30+(dynamixel_gamma*-1),mirror_dynamixel);
  }
  else
  {
    return aCalc(30+dynamixel_gamma,mirror_dynamixel);
  }
}

void setup() {

  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  delay(1000);
  Serial.begin(9600);

}

void loop() {
  //Standing Limit
  //Left-Back
  Dynamixel.moveSpeed(10, dynamixelBeta(11.5,11.5,4,0,0) ,100);
  delay(10);
  Dynamixel.moveSpeed(17, dynamixelAlpha(11.5,11.5,4,0,0) ,100);
  delay(10);
  Dynamixel.moveSpeed(12, dynamixelGamma(11.5,11.5,4,0,0) ,100);
  delay(10);
  //Left-Front
  Dynamixel.moveSpeed(22, dynamixelBeta(11.5,11.5,4,0,0) ,100);
  delay(10);
  Dynamixel.moveSpeed(20, dynamixelAlpha(11.5,11.5,4,0,0) ,100);
  delay(10);
  Dynamixel.moveSpeed(9, dynamixelGamma(11.5,11.5,4,0,0) ,100); 
  delay(10);
  //Right-Back
  Dynamixel.moveSpeed(11, dynamixelBeta(11.5,11.5,4,1,1) ,100);
  delay(10);
  Dynamixel.moveSpeed(18, dynamixelAlpha(11.5,11.5,4,1,1) ,100);
  delay(10);
  Dynamixel.moveSpeed(1, dynamixelGamma(11.5,11.5,4,1,0) ,100);
  delay(10);
  //Right-Front
  Dynamixel.moveSpeed(14, dynamixelBeta(11.5,11.5,4,1,1) ,100);
  delay(10);
  Dynamixel.moveSpeed(5, dynamixelAlpha(11.5,11.5,4,1,1) ,100);
  delay(10);
  Dynamixel.moveSpeed(2, dynamixelGamma(11.5,11.5,4,1,0) ,100);
  delay(10);
}
