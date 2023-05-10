void ultrasonicScan(){
  front_distance  = scan(FRONT);
  left_distance   = scan(LEFT_);
  right_distance  = scan(RIGHT);
  grip_distance   = scan(GRIP);
  
}


void pitchRoll(){
  pitch = getPitch();
  roll = getRoll();
  if(pitch>0){
    pitch = pitch-76;
  }
  if(pitch<0){
    pitch=pitch+76;
  }
}
