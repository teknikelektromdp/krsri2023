void Berdiri(double x_val, double y_val, double z_val){
  //Standing Limit
  //Left-Back
  Dynamixel.moveSpeed(10, AngleCalc(165, 1) ,100);
  delay(10);
  Dynamixel.moveSpeed(17, AngleCalc(130, 1) ,100);
  delay(10);
  Dynamixel.moveSpeed(12, AngleCalc(30, 1) ,100);
  delay(10);
  //Left-Front
  Dynamixel.moveSpeed(22, AngleCalc(165, 1) ,100);
  delay(10);
  Dynamixel.moveSpeed(20, AngleCalc(130, 1) ,100);
  delay(10);
  Dynamixel.moveSpeed(9, AngleCalc(30, 1) ,100);
  delay(10);
  //Right-Back
  Dynamixel.moveSpeed(11, AngleCalc(165, -1) ,400);
  delay(10);
  Dynamixel.moveSpeed(18, AngleCalc(130, -1) ,400);
//  Dynamixel.moveSpeed(18, AngleCalc(AngleMirror(130)), 400);
  delay(10);
  Dynamixel.moveSpeed(1, AngleCalc(30, 1) ,400);
  delay(10);
  //Right-Front
//  Dynamixel.moveSpeed(14, AngleCalc(AngleMirror(TibiaAngle(Beta_Calculation(x_val, y_val, z_val), 1))) ,400);
  Dynamixel.moveSpeed(14, AngleCalc(TibiaAngle(Beta_Calculation(x_val, y_val, z_val), 1), -1) ,400);
  Serial.print("Alpha (Inverse calculation) :");      Serial.println(Beta_Calculation(x_val, y_val, z_val));
  Serial.print("Tibia (Servo angle):");               Serial.println(TibiaAngle(Beta_Calculation(x_val, y_val, z_val), -1));
  Serial.print("Tibia (set angle):");                 Serial.println(tibia_set_angle);
  Serial.print("Tibia (Servo angle increment):");     Serial.println(TibiaAngle(Beta_Calculation(x_val, y_val, z_val), -1) - tibia_set_angle);
//  Serial.print("Tibia (Servo angle w/ set angle):");  Serial.println(tibia_set_angle + TibiaAngle(Beta_Calculation(x_val, y_val, z_val)));
  Serial.print("Tibia (Beta Starting point):");       Serial.println(Beta_Calculation(x_standing, y_standing, z_standing));
  delay(10);
  Dynamixel.moveSpeed(5, AngleCalc(FemurAngle(Alpha_Calculation(x_val, y_val, z_val), 1), 1) ,400);
  Serial.print("\nBeta (Inverse calculation) :");     Serial.println(Alpha_Calculation(x_val, y_val, z_val));
  Serial.print("Femur (Servo angle) :");              Serial.println(FemurAngle(Alpha_Calculation(x_val, y_val, z_val), -1));
  Serial.print("Femur (set angle):");                 Serial.println(femur_set_angle);
  Serial.print("Femur (Servo angle increment):");     Serial.println(FemurAngle(Alpha_Calculation(x_val, y_val, z_val), -1) - femur_set_angle);
//  Serial.print("Femur (Servo angle w/ set angle):");  Serial.println(femur_set_angle + FemurAngle(Alpha_Calculation(x_val, y_val, z_val)));
  Serial.print("Femur (Alpha Starting point):");      Serial.println(Alpha_Calculation(x_standing, y_standing, z_standing));
  delay(10);
  Dynamixel.moveSpeed(2, AngleCalc(CoxaAngle(Gamma_Calculation(x_val, y_val, z_val), 1), 1) ,400);
  Serial.print("\nGamma (Inverse calculation) :");    Serial.println(Gamma_Calculation(x_val, y_val, z_val));
  Serial.print("Coxa (Servo angle) :");               Serial.println(CoxaAngle(Gamma_Calculation(x_val, y_val, z_val), -1));
  Serial.print("Coxa (set angle):");                  Serial.println(coxa_set_angle);
  Serial.print("Coxa (Servo angle increment):");      Serial.println(CoxaAngle(Gamma_Calculation(x_val, y_val, z_val), -1) - coxa_set_angle);
//  Serial.print("Coxa (Servo angle w/ set angle):");   Serial.println(coxa_set_angle + CoxaAngle(Gamma_Calculation(x_val, y_val, z_val)));
  Serial.print("Coxa (Gamma Starting point):");       Serial.println(Gamma_Calculation(x_standing, y_standing, z_standing));
  delay(10);
}
