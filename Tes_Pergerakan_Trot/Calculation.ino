//defining length of each part of the legs
double coxa=7.5,     femur=5,    tibia=6;
//limiting coordinate for leg movement
double x_limit=12.5,  y_limit=12.5, z_limit=3;


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
  
  return beta;
}
//inverse kinematics calculation for femur servo
double Alpha_Calculation(double x, double y, double z){
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


//convert an angle to adc value and mirroring the output
int AngleCalc(float angle, int mirror)
{
  float angle_calc = (angle/300)*1023;
  if(mirror == 1){
    int mirror_angle = (angle_calc - 511)*-1;
    mirror_angle += 511;
    return mirror_angle;
  }
  else{
    return angle_calc;  
  }
}

int dynamixelGamma(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_gamma = Gamma_Calculation(x_limit,y_limit,z_limit)-Gamma_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
    return AngleCalc(30+(dynamixel_gamma*-1),mirror_dynamixel);
  }
  else
  {
    return AngleCalc(30+dynamixel_gamma,mirror_dynamixel);
  }
}


int dynamixelAlpha(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_alpha = Alpha_Calculation(x_limit,y_limit,z_limit) - Alpha_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
    return AngleCalc(150+(dynamixel_alpha*-1), mirror_dynamixel);
  }
  else
  {
    return AngleCalc(150+dynamixel_alpha, mirror_dynamixel);
  }
}


int dynamixelBeta(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_beta = Beta_Calculation(x_limit,y_limit,z_limit) - Beta_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1)
  {
     return AngleCalc(235+(dynamixel_beta*-1), mirror_dynamixel);
  }
  else
  {
    return AngleCalc(235+dynamixel_beta, mirror_dynamixel);
  }
}
