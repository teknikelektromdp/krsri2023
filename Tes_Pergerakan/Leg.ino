void LeftFront(double x_val, double y_val, double z_val){
  //Left-Front
  Dynamixel.moveSpeed(22, dynamixelBeta(x_val, y_val, z_val, 1, 0) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(20, dynamixelAlpha(x_val, y_val, z_val, 0, 0) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(9, dynamixelGamma(x_val, y_val, z_val, 0, 0) ,100);
  delay(servo_speed);
}

void LeftBack(double x_val, double y_val, double z_val){
  //Left-Back
  Dynamixel.moveSpeed(10, dynamixelBeta(x_val, y_val, z_val, 1, 0) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(17, dynamixelAlpha(x_val, y_val, z_val, 0, 0) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(12, dynamixelGamma(x_val, y_val, z_val, 0, 0) ,100);
  delay(servo_speed);
}

void RightFront(double x_val, double y_val, double z_val){
  //Right-Front
  Dynamixel.moveSpeed(14, dynamixelBeta(x_val, y_val, z_val, 1, 1) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(5, dynamixelAlpha(x_val, y_val, z_val, 0, 1) ,100);
  delay(servo_speed);
  Dynamixel.moveSpeed(2, dynamixelGamma(x_val, y_val, z_val, 1, 0) ,100);
  delay(servo_speed);
}
void RightBack(double x_val, double y_val, double z_val){
  //Right-Back
  Dynamixel.moveSpeed(11, dynamixelBeta(x_val, y_val, z_val, 1, 1), 100);
  delay(servo_speed);
  Dynamixel.moveSpeed(18, dynamixelAlpha(x_val, y_val, z_val, 0, 1), 100);
  delay(servo_speed);
  Dynamixel.moveSpeed(1, dynamixelGamma(x_val, y_val, z_val, 1, 0), 100);
  delay(servo_speed);
}
