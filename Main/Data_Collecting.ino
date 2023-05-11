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

void lcdDisplay(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("pitch=");  display.print(pitch);
  display.setCursor(10,0);
  display.print("roll=");  display.print(roll);
  display.setCursor(0,10);
  display.print("cmps=");  display.print(bearing);
  display.setCursor(0,20);
  display.print("b=");  display.print(back_distance);
  display.setCursor(10,20);
  display.print("r=");  display.print(right_distance);
  display.setCursor(0,30);
  display.print("f=");  display.print(front_distance);
  display.setCursor(10,30);
  display.print("l=");  display.print(left_distance);  
}
