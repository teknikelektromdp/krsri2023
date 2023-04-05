#include <DynamixelSerial.h>


double coxa=6,     femur=4.5,    tibia=6;

double x_limit=15,  y_limit=15, z_limit=3;

double x_val=10,    y_val=10,      z_val=3;

double beta_limit=56,      alpha_limit=143;


#define ID_coxa 12
#define ID_femur 17
#define ID_tibia 10

double Rad_to_Degree(double Rad){
  double degree= Rad*57.2957795;
  return degree;
}

double Gamma_Calculation(double x, double y, double z){
  double gamma;
  gamma= Rad_to_Degree(atan(x/y));
  
  return gamma;
}
double Beta_Calculation(double x, double y, double z){
  double L1, beta, L;
  L1=sqrt(pow(x, 2) + pow(y, 2));
  L= sqrt(pow((L1-coxa), 2) + pow(z, 2));
  beta= Rad_to_Degree(acos((pow(tibia, 2) + pow(femur, 2) - pow(L, 2))/(2*tibia*femur)));
  
  return beta;
}
double TotalAlpha_Calculation(double x, double y, double z){
  double L1, L, alpha1, alpha2, alpha_total;
  L1=sqrt(pow(x, 2) + pow(y, 2));
  L= sqrt(pow((L1-coxa), 2) + pow(z, 2));
  alpha1=Rad_to_Degree(acos(z/L));
  alpha2=Rad_to_Degree(acos((pow(femur, 2) + pow(L,2) - pow(tibia, 2))/(2*femur*L)));
  alpha_total=alpha1+alpha2;
  
  return alpha_total;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial1); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
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
  int Kec = 1000;
  // 1 leg test
  

}
