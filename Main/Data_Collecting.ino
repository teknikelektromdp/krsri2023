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
