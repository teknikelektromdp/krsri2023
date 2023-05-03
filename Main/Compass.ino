int16_t getBearing()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPSAddress);

  // Tell register you want some data
  Wire.write(BEARING_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS12
  nReceived = Wire.requestFrom(CMPSAddress , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate full bearing
  _bearing = ((_byteHigh<<8) + _byteLow) / 10;
  
  return _bearing;
}

void compassCalibration(){
  initialPosition(200);
  display.clearDisplay();
  display.setCursor(0,12);
  display.print("Now Calibrating");
  display.display();
  delay(3000);
  //front side
  front_direction = getBearing();
  front_l_offset = front_direction - cmps_offset;
  front_r_offset = front_direction + cmps_offset;

  if(front_l_offset >359){
    front_l_offset = front_l_offset - 360;
  }
  if(front_l_offset < 0){
    front_l_offset = front_l_offset + 360;
  }
  if(front_r_offset >359){
    front_r_offset = front_r_offset - 360;
  }
  if(front_r_offset < 0){
    front_r_offset = front_r_offset + 360;
  }
  Serial.print("Front direction :\t");
  Serial.println(front_direction);
  Serial.print("Left offset :\t");
  Serial.println(front_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(front_r_offset);
  Serial.println("__________________________");

  
  //left side
  left_direction = front_direction - 90;
  left_l_offset = left_direction - cmps_offset;
  left_r_offset = left_direction + cmps_offset;

  if(left_direction >359){
    left_direction = left_direction - 360;
  }
  if(left_direction < 0){
    left_direction = left_direction + 360;
  }
  if(left_l_offset >359){
    left_l_offset = left_l_offset - 360;
  }
  if(left_l_offset < 0){
    left_l_offset = left_l_offset + 360;
  }
  if(left_r_offset >359){
    left_r_offset = left_r_offset - 360;
  }
  if(left_r_offset < 0){
    left_r_offset = left_r_offset + 360;
  }
  
  Serial.print("Left direction :\t");
  Serial.println(left_direction);
  Serial.print("Left offset :\t");
  Serial.println(left_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(left_r_offset);
  Serial.println("__________________________");

  //right side
  right_direction = front_direction + 90;
  right_l_offset = right_direction - cmps_offset;
  right_r_offset = right_direction + cmps_offset;

  if(right_direction >359){
    right_direction = right_direction - 360;
  }
  if(right_direction < 0){
    right_direction = right_direction + 360;
  }
  if(right_l_offset >359){
    right_l_offset = right_l_offset - 360;
  }
  if(right_l_offset < 0){
    right_l_offset = right_l_offset + 360;
  }
  if(right_r_offset >359){
    right_r_offset = right_r_offset - 360;
  }
  if(right_r_offset < 0){
    right_r_offset = right_r_offset + 360;
  }
  
  Serial.print("Right direction :\t");
  Serial.println(right_direction);
  Serial.print("Left offset :\t");
  Serial.println(right_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(right_r_offset);
  Serial.println("__________________________");

  //back side
  back_direction = front_direction - 180;
  back_l_offset = back_direction - cmps_offset;
  back_r_offset = back_direction + cmps_offset;

  if(back_direction >359){
    back_direction = back_direction - 360;
  }
  if(back_direction < 0){
    back_direction = back_direction + 360;
  }
  if(back_l_offset >359){
    back_l_offset = back_l_offset - 360;
  }
  if(back_l_offset < 0){
    back_l_offset = back_l_offset + 360;
  }
  if(back_r_offset >359){
    back_r_offset = back_r_offset - 360;
  }
  if(back_r_offset < 0){
    back_r_offset = back_r_offset + 360;
  }
  
  Serial.print("Back direction :\t");
  Serial.println(back_direction);
  Serial.print("Left offset :\t");
  Serial.println(back_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(back_r_offset);
  Serial.println("________________________________________");

  delay(1000);
  display.clearDisplay();
}
