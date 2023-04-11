//defining length of each part of the legs
double coxa=6.5,     femur=4.7,    tibia=6;
//limiting coordinate for leg movement
double x_limit=11.5,  y_limit=11.5, z_limit=5;

//coordinate value for standing state
double x_standing=11.5,    y_standing=11.5,      z_standing=4;


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


//convert an angle to adc value
int AngleCalc(float angle, int mode)
{
  float angle_calc = (angle/300)*1023;
  if(mode<0){
    int mirror_angle = (angle - 150)*-1;
    mirror_angle += 150;
    return mirror_angle;
  }
  return angle_calc;
}

//calculate the mirror value of an angle
int AngleMirror(int angle)
{
  int mirror_angle = (angle - 150)*-1;
  mirror_angle += 150;
  return mirror_angle;
}

int CoxaAngle(float angle, int mode)
{
  int coxa_angle;
  if (mode < 0){
    coxa_angle = coxa_set_angle - (Gamma_Calculation(x_standing, y_standing, z_standing) - angle);
  }
  else{
    coxa_angle = coxa_set_angle + (Gamma_Calculation(x_standing, y_standing, z_standing) - angle);
  }
  return coxa_angle;
}

int FemurAngle(float angle, int mode)
{
  int femur_angle;
  if (mode < 0){
    femur_angle = femur_set_angle - (Alpha_Calculation(x_standing, y_standing, z_standing) - angle);
  }
  else{
    femur_angle = femur_set_angle + (Alpha_Calculation(x_standing, y_standing, z_standing) - angle);
  }

  return femur_angle;
}

int TibiaAngle(float angle, int mode)
{
  int tibia_angle;
  if (mode < 0){
    tibia_angle = tibia_set_angle - (Beta_Calculation(x_standing, y_standing, z_standing) - angle);
  }
  else {
    tibia_angle = tibia_set_angle + (Beta_Calculation(x_standing, y_standing, z_standing) - angle);
  }
  
  return tibia_angle;
}
