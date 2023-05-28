//defining length of each part of the legs
double gripper_coxa=7.5, gripper_femur=9, gripper_tibia=8.5;
//limiting coordinate for leg movement
double gripper_x_limit=17, gripper_y_limit=17, gripper_z_limit=10;

//inverse kinematics calculation for coxa servo
double Gripper_Gamma_Calculation(double x, double y, double z)
{
  double gamma;
  gamma = Rad_to_Degree(atan(x/y));
  //rounding gamma value
  gamma = round(gamma);
  
  return gamma;
}
//inverse kinematics calculation for tibia servo
double Gripper_Beta_Calculation(double x, double y, double z)
{
  double L1, beta, L;
  L1 =sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-gripper_coxa), 2) + pow(z, 2));
  beta = Rad_to_Degree(acos((pow(gripper_tibia, 2) + pow(gripper_femur, 2) - pow(L, 2))/(2*gripper_tibia*gripper_femur)));
  //rounding beta value
  beta = round(beta);
  
  return beta;
}
//inverse kinematics calculation for femur servo
double Gripper_Alpha_Calculation(double x, double y, double z)
{
  double L1, L, alpha1, alpha2, alpha_total;
  L1 = sqrt(pow(x, 2) + pow(y, 2));
  L  = sqrt(pow((L1-gripper_coxa), 2) + pow(z, 2));
  alpha1 = Rad_to_Degree(acos(z/L));
  alpha2 = Rad_to_Degree(acos((pow(gripper_femur, 2) + pow(L,2) - pow(gripper_tibia, 2))/(2*gripper_femur*L)));
  alpha_total = alpha1 + alpha2;
  //rounding alpha value
  alpha_total = round(alpha_total);

  return alpha_total;
}

int gripperGamma(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_gamma = Gripper_Gamma_Calculation(gripper_x_limit,gripper_y_limit,gripper_z_limit)-Gripper_Gamma_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1){
    return AngleCalc(150+(dynamixel_gamma*-1),mirror_dynamixel);
  }
  else{
    return AngleCalc(150+dynamixel_gamma,mirror_dynamixel);
  }
}

int gripperAlpha(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_alpha = Gripper_Alpha_Calculation(gripper_x_limit,gripper_y_limit,gripper_z_limit) - Gripper_Alpha_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1){
    return AngleCalc(150+(dynamixel_alpha*-1), mirror_dynamixel);
  }
  else{
    return AngleCalc(150+dynamixel_alpha, mirror_dynamixel);
  }
}

int gripperBeta(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_beta = Gripper_Beta_Calculation(gripper_x_limit,gripper_y_limit,gripper_z_limit) - Gripper_Beta_Calculation(x_val,y_val,z_val);
  if(mirror_inverse == 1){
     return AngleCalc(150+(dynamixel_beta*-1), mirror_dynamixel);
  }
  else{
    return AngleCalc(150+dynamixel_beta, mirror_dynamixel);
  }
}

void moveGripper(double x_val,double y_val,double z_val,int speed_)
{
  //coxa
  Dynamixel.moveSpeed(7,gripperGamma(x_val,y_val,z_val,1,0),speed_);
  delay(10);
  //femur
  Dynamixel.moveSpeed(16,gripperAlpha(x_val,y_val,z_val,0,0),speed_);
  delay(10);
  //tibia
  Dynamixel.moveSpeed(8,gripperBeta(x_val,y_val,z_val,0,0),speed_);
  delay(10);
}

void liftPosition()
{
  //coxa
  Dynamixel.moveSpeed(7,500,150);
  delay(10);
  //femur
  Dynamixel.moveSpeed(16,200,150);
  delay(10);
  //tibia
  Dynamixel.moveSpeed(8,300,150);
  delay(10);
  pixy.setServos(0,1000);
}
void gripMovement(String movement)
{
  //pixy.setServos(lifter, gripper)  limit (300-1000, 0-500)
  //lcg = lift and close gripper 
  if(movement == "lcg")
  {
    pixy.setServos(100, 0);
  }
  //lift and open gripper
  else if(movement == "log")
  {
    pixy.setServos(100, 500);
  }
  //put and open gripper
  else if(movement == "pog")
  {
    pixy.setServos(850, 500);
  }
  //put and close gripper
  else if(movement == "pcg"){
    pixy.setServos(850, 0);
  }
  //lift the victim a bit
  else if(movement == "lch"){
    pixy.setServos(700,0);
  }
  //open and lift by a bit
  else if(movement == "loh"){
    pixy.setServos(700,500);
  }
  //put(to scan) and open gripper
  else if(movement == "sog"){
    pixy.setServos(900, 500);
  }
  else if(movement == "grip"){
    pixy.setServos(0,1000);
  }
  else if(movement == "open"){
    pixy.setServos(0,500);
  }
  else
  {
    pixy.setServos(1000, 500);
  }
}

void initGripper()
{
//  gripMovement("lcg");
  liftPosition();
  pixy.setServos(0,1000);
  //turn on the led
  pixy.setLamp(0, 0);
}
