//int16_t getBearing()
//{
//  // Begin communication with CMPS12
//  Wire.beginTransmission(CMPS12Address);
//
//  // Tell register you want some data
//  Wire.write(BEARING_Register);
//
//  // End the transmission
//  int nackCatcher = Wire.endTransmission();
//
//  // Return if we have a connection problem 
//  if(nackCatcher != 0){return 0;}
//  
//  // Request 1 bytes from CMPS12
//  nReceived = Wire.requestFrom(CMPS12Address , ONE_BYTE);
//
//  // Something has gone wrong
//  if (nReceived !=ONE_BYTE) return 0;
//
//  // Read the values
//  _byteHigh = Wire.read(); 
//  _byteLow = Wire.read();
//
//  // Calculate full bearing
//  _bearing = ((_byteHigh<<8) + _byteLow) / 10;
//  
//  return _bearing;
//}

int16_t getBearing(){
  unsigned char high_byte, low_byte, angle8;
  unsigned int angle16;
  Wire.beginTransmission(CMPS12Address);  //starts communication with CMPS12
  Wire.write(1);                     //Sends the register we wish to start reading from
  Wire.endTransmission();
 
  // Request 5 bytes from the CMPS12
  // this will give us the 8 bit bearing, 
  // both bytes of the 16 bit bearing, pitch and roll
  Wire.requestFrom(CMPS12Address, 5);       
  
  while(Wire.available() < 5);        // Wait for all bytes to come back
  
  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
  pitch = Wire.read();
  roll = Wire.read();
  
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
    
//  Serial.print("    angle full: ");     // Display 16 bit angle with decimal place
//  Serial.print(angle16 / 10, DEC);
//  Serial.print(".");
//  Serial.print(angle16 % 10, DEC);
//  
//  Serial.print("    angle 8: ");        // Display 8bit angle
//  Serial.println(angle8, DEC);
  _bearing =angle8;

  return _bearing;
}

void compassAutoCalibration(){
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
  writeLog("Front direction :\t");
  writeLog(intToString(front_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(front_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(front_r_offset));
  writeLog("__________________________");
  
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
  writeLog("Left direction :\t");
  writeLog(intToString(left_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(left_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(left_r_offset));
  writeLog("__________________________");

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
  writeLog("Right direction :\t");
  writeLog(intToString(right_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(right_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(right_r_offset));
  writeLog("__________________________");

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
  writeLog("Back direction :\t");
  writeLog(intToString(back_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(back_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(back_r_offset));
  writeLog("________________________________________");

  delay(1000);
  display.clearDisplay();
}

void compassManualCalibration(int front_facing){
  front_direction = front_facing;
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
//  Serial.print("Front direction :\t");
//  Serial.println(front_direction);
//  Serial.print("Left offset :\t");
//  Serial.println(front_l_offset);
//  Serial.print("Right offset :\t");
//  Serial.println(front_r_offset);
//  Serial.println("__________________________");
//  writeLog("Front direction :\t");
//  writeLog(intToString(front_direction));
//  writeLog("Left offset :\t");
//  writeLog(intToString(front_l_offset));
//  writeLog("Right offset :\t");
//  writeLog(intToString(front_r_offset));
//  writeLog("__________________________");
  
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
  
//  Serial.print("Left direction :\t");
//  Serial.println(left_direction);
//  Serial.print("Left offset :\t");
//  Serial.println(left_l_offset);
//  Serial.print("Right offset :\t");
//  Serial.println(left_r_offset);
//  Serial.println("__________________________");
//  writeLog("Left direction :\t");
//  writeLog(intToString(left_direction));
//  writeLog("Left offset :\t");
//  writeLog(intToString(left_l_offset));
//  writeLog("Right offset :\t");
//  writeLog(intToString(left_r_offset));
//  writeLog("__________________________");

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
  
//  Serial.print("Right direction :\t");
//  Serial.println(right_direction);
//  Serial.print("Left offset :\t");
//  Serial.println(right_l_offset);
//  Serial.print("Right offset :\t");
//  Serial.println(right_r_offset);
//  Serial.println("__________________________");
//  writeLog("Right direction :\t");
//  writeLog(intToString(right_direction));
//  writeLog("Left offset :\t");
//  writeLog(intToString(right_l_offset));
//  writeLog("Right offset :\t");
//  writeLog(intToString(right_r_offset));
//  writeLog("__________________________");

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
  
//  Serial.print("Back direction :\t");
//  Serial.println(back_direction);
//  Serial.print("Left offset :\t");
//  Serial.println(back_l_offset);
//  Serial.print("Right offset :\t");
//  Serial.println(back_r_offset);
//  Serial.println("________________________________________");
//  writeLog("Back direction :\t");
//  writeLog(intToString(back_direction));
//  writeLog("Left offset :\t");
//  writeLog(intToString(back_l_offset));
//  writeLog("Right offset :\t");
//  writeLog(intToString(back_r_offset));
//  writeLog("________________________________________");
}

void compassManualCalibration8bit(int front_facing){
  front_direction = front_facing;
  front_l_offset = front_direction - cmps_offset;
  front_r_offset = front_direction + cmps_offset;

  if(front_l_offset >255){
    front_l_offset = front_l_offset - 256;
  }
  if(front_l_offset < 0){
    front_l_offset = front_l_offset + 256;
  }
  if(front_r_offset >255){
    front_r_offset = front_r_offset - 256;
  }
  if(front_r_offset < 0){
    front_r_offset = front_r_offset + 256;
  }
    Serial.print("Front direction :\t");
  Serial.println(front_direction);
  Serial.print("Left offset :\t");
  Serial.println(front_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(front_r_offset);
  Serial.println("__________________________");
  writeLog("Front direction :\t");
  writeLog(intToString(front_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(front_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(front_r_offset));
  writeLog("__________________________");
  //left side
  left_direction = front_direction - 64;
  left_l_offset = left_direction - cmps_offset;
  left_r_offset = left_direction + cmps_offset;

  if(left_direction >255){
    left_direction = left_direction - 256;
  }
  if(left_direction < 0){
    left_direction = left_direction + 256;
  }
  if(left_l_offset >255){
    left_l_offset = left_l_offset - 256;
  }
  if(left_l_offset < 0){
    left_l_offset = left_l_offset + 256;
  }
  if(left_r_offset >255){
    left_r_offset = left_r_offset - 256;
  }
  if(left_r_offset < 0){
    left_r_offset = left_r_offset + 256;
  }
  Serial.print("Left direction :\t");
  Serial.println(left_direction);
  Serial.print("Left offset :\t");
  Serial.println(left_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(left_r_offset);
  Serial.println("__________________________");
  writeLog("Left direction :\t");
  writeLog(intToString(left_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(left_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(left_r_offset));
  writeLog("__________________________");
  //right side
  right_direction = front_direction + 64;
  right_l_offset = right_direction - cmps_offset;
  right_r_offset = right_direction + cmps_offset;

  if(right_direction >255){
    right_direction = right_direction - 256;
  }
  if(right_direction < 0){
    right_direction = right_direction + 256;
  }
  if(right_l_offset >255){
    right_l_offset = right_l_offset - 256;
  }
  if(right_l_offset < 0){
    right_l_offset = right_l_offset + 256;
  }
  if(right_r_offset >255){
    right_r_offset = right_r_offset - 256;
  }
  if(right_r_offset < 0){
    right_r_offset = right_r_offset + 256;
  }
    Serial.print("Right direction :\t");
  Serial.println(right_direction);
  Serial.print("Left offset :\t");
  Serial.println(right_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(right_r_offset);
  Serial.println("__________________________");
  writeLog("Right direction :\t");
  writeLog(intToString(right_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(right_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(right_r_offset));
  writeLog("__________________________");
  //back side
  back_direction = front_direction - 128;
  back_l_offset = back_direction - cmps_offset;
  back_r_offset = back_direction + cmps_offset;

  if(back_direction >255){
    back_direction = back_direction - 256;
  }
  if(back_direction < 0){
    back_direction = back_direction + 256;
  }
  if(back_l_offset >255){
    back_l_offset = back_l_offset - 256;
  }
  if(back_l_offset < 0){
    back_l_offset = back_l_offset + 256;
  }
  if(back_r_offset >255){
    back_r_offset = back_r_offset - 256;
  }
  if(back_r_offset < 0){
    back_r_offset = back_r_offset + 256;
  }
    Serial.print("Back direction :\t");
  Serial.println(back_direction);
  Serial.print("Left offset :\t");
  Serial.println(back_l_offset);
  Serial.print("Right offset :\t");
  Serial.println(back_r_offset);
  Serial.println("________________________________________");
  writeLog("Back direction :\t");
  writeLog(intToString(back_direction));
  writeLog("Left offset :\t");
  writeLog(intToString(back_l_offset));
  writeLog("Right offset :\t");
  writeLog(intToString(back_r_offset));
  writeLog("________________________________________");
}

byte getPitch()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPS12Address);

  // Tell register you want some data
  Wire.write(PITCH_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}

  // Request 1 byte from CMPS12
  nReceived = Wire.requestFrom(CMPS12Address , ONE_BYTE);

  // Something has gone wrong
  if (nReceived != ONE_BYTE) return 0;

  // Read the values
  _pitch = Wire.read();

  return _pitch;
}

byte getRoll()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPS12Address);

  // Tell register you want some data
  Wire.write(ROLL_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 1 byte from CMPS12
  nReceived = Wire.requestFrom(CMPS12Address , ONE_BYTE);

  // Something has gone wrong
  if (nReceived != ONE_BYTE) return 0;

  // Read the values
  _roll = Wire.read();

  return _roll ;
}
