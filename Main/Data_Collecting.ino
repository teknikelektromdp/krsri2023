void ultrasonicScan(){
  gripMovement("pcg");
  initialPosition(200);
  writeLog("Front Distance");
  writeLog(intToString(scan(FRONT)));
  writeLog("Left Distance");
  writeLog(intToString(scan(LEFT_)));
  writeLog("Right Distance");
  writeLog(intToString(scan(RIGHT)));
  writeLog("Back Distance");
  writeLog(intToString(scan(GRIP)));
  writeLog("------------------------");
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
