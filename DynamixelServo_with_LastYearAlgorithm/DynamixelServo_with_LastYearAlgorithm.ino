#include <DynamixelSerial.h>

//Servo address
int servoLFT = ,
    servoLFM = ,
    servoLFB = ,
    
    servoLBT = ,
    servoLBM = ,
    servoLBB = ,
    
    servoRFT = ,
    servoRFM = ,
    servoRFB = ,
    
    servoRBT = ,
    servoRBM = ,
    servoRBB = ;


void Berdiri(int kecepatan){
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);

  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);

  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
  
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
  Dynamixel.moveSpeed( , 500, kecepatan);
}

void setup() {
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial2); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,5);  // Inicialize the servo at 1 Mbps and Pin Control 2
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Berdiri(500);
}
