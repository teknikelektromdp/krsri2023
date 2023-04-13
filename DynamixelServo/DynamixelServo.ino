#include <DynamixelSerial.h>

//last try = 22
#define ID 1

/*
 * Kecepatan maksimum putar servo per sudut sekitar 1.65385 ms
 */

void TesPutar(int kecepatan){
    for(int i =0; i<=1000; i++){
    Dynamixel.moveSpeed(ID,i,kecepatan);
//    delay(5);
  }
  delay(1000);
  for(int i =1000; i>=0; i--){
    Dynamixel.moveSpeed(ID,i,kecepatan);
//    delay(5);
  }
  delay(1000);
}
void TesPinpoint(int kecepatan){
  Dynamixel.moveSpeed(ID,0,kecepatan);
//  Serial.println("0");
  delay(3000);
  Dynamixel.moveSpeed(ID,250,kecepatan);
//  Serial.println("1000");
  delay(3000);
}

//void gerakKaki(int n){
//  for(int i;i<=15;i++){
//    Dynamixel.moveSpeed()
//  }
//  
//}


void setup(){
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial1); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
  Dynamixel.begin(1000000,15);  // Inicialize the servo at 1 Mbps and Pin Control 5
  delay(1000);
}

void loop(){
  int Kec = 500;

//  TesPutar(Kec);
//  TesPinpoint(Kec);

//  for(int id=0; id<=30; id++){
//    Dynamixel.moveSpeed(id,0,Kec);
//  }
//  delay(3000);
//  for(int id1=0; id1<=30; id1++){
//    Dynamixel.moveSpeed(id1,1000,Kec);
//  }
//  delay(4000);
//
//  for(int i=0; i<60;i++){
//    Dynamixel.moveSpeed(i,500,Kec);
//    Serial.println(i);
//    delay(1000);
//  }
//  Serial.println("Recalibration to 500 is Done");
//  for(int i=0; i<60;i++){
//    Dynamixel.moveSpeed(i,1000,Kec);
//    Serial.println(i);
//    delay(500);
//  }
//  Serial.println("Recalibration to 1000 is Done");
//
//  Dynamixel.moveSpeed(13,500,Kec);
  Dynamixel.moveSpeed(14,750,Kec);
//  
  Dynamixel.moveSpeed(2,500,Kec);
  Dynamixel.moveSpeed(5,500,Kec);
//  
//  Dynamixel.moveSpeed(10,500,Kec);
//  Dynamixel.moveSpeed(11,500,Kec);
//
  Dynamixel.moveSpeed(20,500,Kec);
  Dynamixel.moveSpeed(9,500,Kec);
//
//  Serial.println("Recalibration to 1000 is Done");
}
