void getGyro(){
  gyrox = getGyroX() * _gyroScale;
  gyroy = getGyroY() * _gyroScale;
  gyroz = getGyroZ() * _gyroScale;
  Serial.print("\t$GYR,");
  Serial.print(gyrox,4);
  Serial.print(",");
  Serial.print(gyroy,4); 
  Serial.print(",");
  Serial.print(gyroz,4);
  Serial.println(" degree/s");
}
int16_t getGyroX()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPS12Address);

  // Tell register you want some data
  Wire.write(_Register_GYRO_X);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS12
  nReceived = Wire.requestFrom(CMPS12Address , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate GryoX
  return ((_byteHigh<<8) + _byteLow);
}

int16_t getGyroY()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPS12Address);

  // Tell register you want some data
  Wire.write(_Register_GYRO_Y);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS12
  nReceived = Wire.requestFrom(CMPS12Address , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate GryoY
  return ((_byteHigh<<8) + _byteLow);
}

int16_t getGyroZ()
{
  // Begin communication with CMPS12
  Wire.beginTransmission(CMPS12Address);

  // Tell register you want some data
  Wire.write(_Register_GYRO_Z);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS12
  nReceived = Wire.requestFrom(CMPS12Address , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate GryoZ
  return ((_byteHigh<<8) + _byteLow);
}
