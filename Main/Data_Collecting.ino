void ultrasonicScan(){
  front_distance  = scan(FRONT);
  left_distance   = scan(LEFT_);
  right_distance  = scan(RIGHT);
  back_distance   = scan(GRIP);
}


void pitchRoll(){
  pitch = getPitch();
  roll = getRoll();
  Serial.print(pitch);
  Serial.print(", ");
  Serial.print(roll);
//      writeLog(byteToString(getPitch()));
  if(pitch>0){
    pitch = pitch-76;
  }
  if(pitch<0){
    pitch=pitch+76;
  }
  Serial.print("\t\t");
  Serial.print(pitch);
  Serial.print(", ");
  Serial.println(roll);
}
