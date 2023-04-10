double coxa=6.5,     femur=4.7,      tibia=6;

double x_limit=11.5,  y_limit=11.5, z_limit=5;

double x_val=11.5,    y_val=11.5,      z_val=4;

double Rad_to_Degree(double Rad){
  double degree= Rad*57.2957795;
  return degree;
}
//Source Code
//double Inverse_Calculation(double x, double y, double z){
//  double L1, gamma, beta, L, alpha1, alpha2, alpha_total;
//  L1=sq(pow(x, 2) + pow(y, 2));
//  gamma= Rad_to_Degree(atan(x/y));
//  L= sq(pow((L1-coxa), 2) + pow(z, 2));
//  beta= Rad_to_Degree(acos((pow(tibia, 2) + pow(femur, 2) - pow(L, 2))/(2*tibia*femur)));
//  alpha1=Rad_to_Degree(acos(z/L));
//  alpha2=Rad_to_Degree(acos((pow(femur, 2) + pow(L,2) - pow(tibia, 2))/(2*femur*L)));
//  alpha_total=alpha1+alpha2;
//  return gamma, beta, alpha_total;
//}
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
//  alpha1=acos(z/L);
//  alpha2=acos((pow(femur, 2) + pow(L,2) - pow(tibia, 2))/(2*femur*L));

  alpha_total=alpha1+alpha2;
  return alpha_total;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hasil Kalkulasi(Float)");
  Serial.print("Gamma=");
  Serial.println(Gamma_Calculation(x_val,y_val,z_val));
  Serial.print("Beta=");
  Serial.println(Beta_Calculation(x_val,y_val,z_val));
  Serial.print("Alpha total=");
  Serial.println(TotalAlpha_Calculation(x_val,y_val,z_val));
}

void loop() {
  // put your main code here, to run repeatedly:

}
