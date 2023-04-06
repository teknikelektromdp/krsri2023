#include <DynamixelSerial.h>

//defining length of each part of the legs
double coxa=6,     femur=4.5,    tibia=6;
//limiting coordinate for leg movement
double x_limit=15,  y_limit=15, z_limit=3;
//limiting servo rotation's degree of freedom
double beta_limit=75,      alpha_limit=90;

//coordinate value for standing state
double x_val=11,    y_val=11,      z_val=3;

//defining id for 1 leg
#define ID_coxa 9
#define ID_femur 20
#define ID_tibia 22

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
double Gamma_Calculation(double x, double y, double z){
  double gamma;
  gamma = Rad_to_Degree(atan(x/y));
  //rounding gamma value
  gamma = round(gamma);
  //mapping from 0-300 (physical capability of servo) to 0-1000 (digitally signed servo capability)
  gamma = map(gamma, 0, 300, 0, 1000);
  return gamma;
}

//inverse kinematics calculation for tibia servo
double Beta_Calculation(double x, double y, double z){
  double L1, beta, L;
  L1 =sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-coxa), 2) + pow(z, 2));
  beta = Rad_to_Degree(acos((pow(tibia, 2) + pow(femur, 2) - pow(L, 2))/(2*tibia*femur)));
  //rounding beta value
  beta = round(beta);
  //mapping from 0-300 (physical capability of servo) to 0-1000 (digitally signed servo capability)
  beta = map(beta, 0, 300, 0, 1000);
  return beta;
}

//inverse kinematics calculation for femur servo
double TotalAlpha_Calculation(double x, double y, double z){
  double L1, L, alpha1, alpha2, alpha_total;
  L1 = sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-coxa), 2) + pow(z, 2));
  alpha1 = Rad_to_Degree(acos(z/L));
  alpha2 = Rad_to_Degree(acos((pow(femur, 2) + pow(L,2) - pow(tibia, 2))/(2*femur*L)));
  alpha_total = alpha1 + alpha2;
  //rounding alpha value
  alpha_total = round(alpha_total);
  //mapping from 0-300 (physical capability of servo) to 0-1000 (digitally signed servo capability)
  alpha_total = map(alpha_total, 0, 300, 0, 1000);
  return alpha_total;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial2); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,5);  // Inicialize the servo at 1 Mbps and Pin Control 2
  delay(1000);
  Serial.println("Hasil Kalkulasi");
  Serial.print("Gamma=");
  Serial.println(Gamma_Calculation(x_val,y_val,z_val));
  Serial.print("Beta=");
  Serial.println(Beta_Calculation(x_val,y_val,z_val));
  Serial.print("Alpha total=");
  Serial.println(TotalAlpha_Calculation(x_val,y_val,z_val));
  Serial.println("Hasil Kalkulasi (rounded version");
  Serial.print("Gamma=");
  Serial.println(round(Gamma_Calculation(x_val,y_val,z_val)));
  Serial.print("Beta=");
  Serial.println(round(Beta_Calculation(x_val,y_val,z_val)));
  Serial.print("Alpha total=");
  Serial.println(round(TotalAlpha_Calculation(x_val,y_val,z_val)));
}

void loop() {
  int Kec = 500;
//  // 1 leg test for standing state
//  Dynamixel.moveSpeed(ID_coxa, Gamma_Calculation(x_val,y_val,z_val), Kec);
//  Dynamixel.moveSpeed(ID_femur, TotalAlpha_Calculation(x_val,y_val,z_val), Kec); 
//  Dynamixel.moveSpeed(ID_tibia, Beta_Calculation(x_val, y_val, z_val), Kec);

  Dynamixel.moveSpeed(ID_coxa, 0, Kec);
  Dynamixel.moveSpeed(ID_femur, 0, Kec); 
  Dynamixel.moveSpeed(ID_tibia, 0, Kec);
}
