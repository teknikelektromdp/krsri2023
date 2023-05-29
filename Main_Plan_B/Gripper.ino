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
  
}
void gripMovement(String movement)
{
  //lcg = lift and close gripper 
  if(movement == "lcg")
  {
    //coxa
    Dynamixel.moveSpeed(7,500,175);
    delay(10);
    //femur
    Dynamixel.moveSpeed(16,200,175);
    delay(10);
    //tibia
    Dynamixel.moveSpeed(8,300,175);
    delay(10);
    Gripper.write(150);
  }
  //lift and open gripper
  else if(movement == "log")
  {
    Dynamixel.moveSpeed(7,500,175);
    delay(10);
    //femur
    Dynamixel.moveSpeed(16,200,175);
    delay(10);
    //tibia
    Dynamixel.moveSpeed(8,300,175);
    delay(10);
    Gripper.write(90);
  }
  //put(to scan) and open gripper
  else if(movement == "sog"){
    Dynamixel.moveSpeed(7,600,250);
    delay(100);
    //tibia
    Dynamixel.moveSpeed(8,100,250);
    //femur
    Dynamixel.moveSpeed(16,750,250);
    delay(100);
    
    //tibia
    Dynamixel.moveSpeed(8,300,250);
    gripMovement("open");
  }
  else if(movement == "take"){
    //femur
    Dynamixel.moveSpeed(16,675,150);
    delay(10);
    //tibia
    Dynamixel.moveSpeed(8,350,150);
    delay(500);
    gripMovement("grip");
    delay(1000);

    Dynamixel.moveSpeed(8,200,150);
    delay(500);
    Dynamixel.moveSpeed(16,700,150);
  }
  else if(movement == "grip"){
    Gripper.write(160);
  }
  else if(movement == "open"){
    Gripper.write(90);
  }
  else if(movement == "put"){
    Dynamixel.moveSpeed(7,520,150);
    delay(10);
    //femur
    Dynamixel.moveSpeed(16,800,150);
    delay(10);
    //tibia
    Dynamixel.moveSpeed(8,200,150);
  }
  else
  {
    pixy.setServos(1000, 500);
  }
}

void initGripper()
{
//  Gripper.attach(4);
  gripMovement("lcg");
//  liftPosition();
  
//  Gripper.write();
  //turn on the led
  pixy.setLamp(0, 0);
}
