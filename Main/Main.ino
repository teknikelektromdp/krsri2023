/*Libraries*/
#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Pixy2.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Constants*/
//Menu
#define MENU_SIZE 3
//Button
#define menu_button 3
#define start_button 11
//I2C address
#define CMPS12Address 0x60
//Ultrasonic
#define RBD A0 //Right Back Diagonal
#define RFD A2 //Right Front Diagonal
#define LBD 9 //Left Back Diagonal
#define LFD 8 //Left Front Diagonal
#define GRIP A9 //Gripper
#define FRONT A8//Front
#define LEFT_ A6//Left
#define RIGHT A4//Right
//Compass
#define BEARING_Register 2
#define PITCH_Register 4 
#define ROLL_Register 5
#define TWO_BYTES 2
#define ONE_BYTE 1
//Gyroscope
#define _Register_GYRO_X 18
#define _Register_GYRO_Y 20
#define _Register_GYRO_Z 22


/*Push buttons + Menu*/
int menuState = LOW,
    startState = LOW,
    menuCount = 0,
    start_ = 0,
    cursor = 0,
    start_count = 0,
    startPressed = 0,    
    endPressed = 0,     
    holdTime = 0,        
    idleTime = 0;        
long lastDebounceTime = 0,  
      debounceDelay = 300;
char *menu[MENU_SIZE] = { "Calibration", "Enable PID", "Disable PID" };

/*IK*/
int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
int lastPositionLFX, lastPositionLFY, lastPositionLFZ,
    lastPositionLBX, lastPositionLBY, lastPositionLBZ,
    lastPositionRFX, lastPositionRFY, lastPositionRFZ,
    lastPositionRBX, lastPositionRBY, lastPositionRBZ;
double  x_default=8,//(8),
        y_default=8,//(8)
        z_default=5;//5

/*Pixy*/
int left_min, 
    left_max, 
    right_min, 
    right_max, 
    front_min, 
    front_max, 
    lock, 
    object1;
    
/*COMPASS*/
int nReceived,
    _bearing;
int cmps_offset=10,
    front_direction,  front_r_offset, front_l_offset,
    left_direction,   left_r_offset,  left_l_offset,
    right_direction,  right_r_offset, right_l_offset,
    back_direction,   back_r_offset,  back_l_offset;
byte _byteHigh,
     _byteLow;
char _pitch,//on steep obstacle = +- 13~14
     _roll;//on steep obstacle = +- 11~13
signed char pitch;
signed char roll;
/*Gyroscope*/
float gyrox = 0;
float gyroy = 0;
float gyroz = 0;
float _gyroScale = 1.0f/16.f; // 1 Dps = 16 LSB

/* Data Logger */
const byte address[6] = "00001";

/*Classes*/
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
Pixy2 pixy;
RF24 radio(A7, A5); // CE, CSN

void(*resetFunc)(void)=0;

void setup(){
  Serial.begin(9600);
  //Starting Dynamixel servo
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  initLogger();
  pinMode(menu_button, INPUT);
  pinMode(start_button, INPUT);
  attachInterrupt(digitalPinToInterrupt(menu_button), mainMenu, CHANGE);
  display.begin();
  display.setPowerSave(0);
  display.setFont(u8x8_font_pxplusibmcgathin_f);
  display.drawString(0,0,"MDP Engine Bot");
  initPixy();
  initGripper();
  initialPosition(200);
  delay(1000);
}

void loop() 
{
  // detectObject(1);
   displayMenu();
//  getObjectLocation()
  gripMovement("lcg");
  pixy.setLamp(0,0);
//  ultrasonicScan();
  int right_distance = scan(RIGHT),
      front_distance;

  int offsetkiri=48, offsetkanan=58;

/*  testing purpose  
  int mundur=0;
  int bearing;
  compassManualCalibration(50);
  while(true){
    int speed = 400, delay_servo = 10;
    RightFront(5,7,6,speed,delay_servo);
    LeftBack(5,7,7,speed,delay_servo);
    LeftFront(7,5,2,speed,delay_servo);
    RightBack(7,5,3,speed,delay_servo);
    delay(50);
    LeftFront(5,7,6,speed,delay_servo);
    RightBack(5,7,7,speed,delay_servo);
    RightFront(7,5,2,speed,delay_servo);
    LeftBack(7,5,3,speed,delay_servo);
    delay(50);
//    enhancedTrotBackwardv2(400,2);
  }
*/



//for(int i=0; i<5; i++){90 degree Left turn
//      enhancedTrotHigherLeftTurn(500,10);
//    }

compassManualCalibration(50);
//  for(int i=0; i<5; i++){
//    enhancedTrotHigherRightTurn(500,10);
//  }
//  delay(4000);
//  initialPosition(200);
//  delay(2000);


  //starting from home
  while(true)
  {
    int k=0, repositioning,bearing, home_=0; 
    bearing = getBearing();
    while(home_==0){
      bearing = getBearing();
      if(bearing<front_r_offset && bearing>front_l_offset){
        home_=1;
      }
      else if(bearing < front_l_offset || bearing>back_r_offset){
//        enhancedTrotLowerRightTurn(500,10);
        for(int i=0; i<5; i++){
          enhancedTrotHigherRightTurn(500,10);
        }
//        home_=1;
      }
      else if(bearing<back_l_offset && bearing>front_r_offset){
//        enhancedTrotLowerLeftTurn(500,10);
        for(int i=0; i<5; i++){
          enhancedTrotHigherLeftTurn(500,10);
        }
//        home_=1;
      }
      else{
        for(int i=0; i<10; i++){
          enhancedTrotHigherLeftTurn(500,10);
        }
//        home_=1;
      }
      delay(10);
    }
  repositioning=0;
  while(k ==0){
    while(right_distance<=54){
      trotBasicLeftward(250, 8);
      right_distance=scan(RIGHT);
    }
    
    while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5,5);
      display.print(bearing);
      display.display();
      if(bearing<offsetkiri){
        enhancedTrotLowerRightTurn(250,10);
      }
      else if(bearing>offsetkanan){
        enhancedTrotLowerLeftTurn(250,10);
      }
      else{
        repositioning=1;
      }
    }
    right_distance=scan(RIGHT);
    
    if(right_distance >54 && bearing >=offsetkiri && bearing<=offsetkanan){
      k=1;
    }
    else{
      k=0;
    }
  }
  /*  Taking victim(s)  */
//    writeLog("SAVING VICTIM");
    pixy.setLamp(1,0);
    gripMovement("sog");
    detectObject(1);
    gripMovement("pcg");
    delay(200);
    gripMovement("lch");
    delay(200);
    front_distance =scan(FRONT);
    while(front_distance>15){
      trotBasicForward(130,10);
      delay(10);
      front_distance=scan(FRONT);
    }
    
    repositioning=0;
    while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5,5);
      display.print(bearing);
      display.display();
      if(bearing<offsetkiri){
        enhancedTrotLowerRightTurn(250,10);
      }
      else if(bearing>offsetkanan){
        enhancedTrotLowerLeftTurn(250,10);
      }
      else{
        repositioning=1;
      }
    }
    gripMovement("lcg");
    pixy.setLamp(0,0);
    delay(100);
    initialPosition(200);
    delay(100);
    
    int mundur=0,kanan=0;
    pitchRoll();
//    while(abs(pitch) < 15 && abs(roll)<15){
    while(true){
      enhancedTrotHigherLeft(500,12);
      bearing =getBearing();
      if(bearing>right_direction-20.
      0){
        mundur=1;
      }
      
      while(mundur==1){
        enhancedTrotHigherBackward(500,12);
        bearing=getBearing();
        
        if(bearing>back_direction-20){
          kanan=1;
        }
        while(kanan==1){
          enhancedTrotHigherRight(500,12);
          pitchRoll();
          display.clearDisplay();
          display.setCursor(0,0);
          display.print(pitch);
          display.setCursor(10,0);
          display.print(roll);
          display.display();
//          if(abs(pitch)>10 || abs(roll)>10){
//            kanan=0;
//          }
        }
        pitchRoll();
        display.clearDisplay();
        display.setCursor(0,0);
        display.print(pitch);
        display.setCursor(10,0);
        display.print(roll);
        display.display();
//        if(abs(pitch)>13 || abs(roll)>13){
//          mundur=0;
//        }
      }
      pitchRoll();
    }
    display.clearDisplay();
    display.setCursor(0,0);

    display.print("miring");
    display.display();
    repositioning=0;
    while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(10,10);
      display.print(bearing);
      display.display();
      if(bearing<right_l_offset){
        enhancedTrotLowerRightTurn(400,10);
      }
      else if(bearing>right_r_offset){
        enhancedTrotLowerLeftTurn(400,10);
      }
      else{
        repositioning=1;
      }
    }
    pitchRoll();
    while(abs(pitch) > 2 || abs(roll)>2){
      enhancedTrotBackward(400);
      pitchRoll();
    }
    repositioning=0;
    while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(10,10);
      display.print(bearing);
      display.display();
      if(bearing<right_l_offset){
        enhancedTrotLowerRightTurn(250,10);
      }
      else if(bearing>right_r_offset){
        enhancedTrotLowerLeftTurn(250,10);
      }
      else{
        repositioning=1;
      }
    }
    initialPosition(200);
    delay(20000000);
//  while(true){
//    initialPosition(200);
//    pixy.setLamp(0,0);
//    delay(200);
//    pixy.setLamp(1,1);
//    delay(200);
//    bearing = getBearing();
//    display.setCursor(10,10);
//    display.print(bearing);
//    display.display();
//  }
    
//    enhancedTrotHigherLeftTurn(200, 10);
    
    
//    int i=5, n=8, j=3, fast_speed=500, delay_servo=1;
////    fastMove(600);
////    trotBasicForward(300,10);
//    //Forward Movement
//      RightFront(8,i,j, fast_speed, delay_servo);
//      LeftBack(8,i,j, fast_speed, delay_servo);
//      LeftFront(8,n,j, fast_speed, delay_servo);
//      RightBack(8,n,j, fast_speed, delay_servo);
//      delay(10);
//    LeftFront(8,i,j, fast_speed, delay_servo);
//    RightBack(8,i,j, fast_speed, delay_servo);
//    RightFront(8,n,j, fast_speed, delay_servo);
//    LeftBack(8,n,j, fast_speed, delay_servo);
//    delay(10);

    //backward  movement
//      RightFront(i,8,j, fast_speed, delay_servo);
//      LeftBack(i,8,j, fast_speed, delay_servo);
//      LeftFront(8,n,j, fast_speed, delay_servo);
//      RightBack(8,n,j, fast_speed, delay_servo);
//      delay(10);
//    LeftFront(i,8,j, fast_speed, delay_servo);
//    RightBack(i,8,j, fast_speed, delay_servo);
//    RightFront(8,n,j, fast_speed, delay_servo);
//    LeftBack(8,n,j, fast_speed, delay_servo);
//    delay(10);


    //left movement
//    LeftFront(6,8,2.5,fast_speed,delay_servo);
//    RightBack(6,8,2.5,fast_speed,delay_servo);
//    RightFront(6,8,2,fast_speed,delay_servo);
//    LeftBack(6,8,2,fast_speed,delay_servo);
//    delay(1);
//    RightFront(8,6,2.5,fast_speed,delay_servo);
//    LeftBack(8,6,2.5,fast_speed,delay_servo);
//    LeftFront(8,6,2,fast_speed,delay_servo);
//    RightBack(8,6,1.5,fast_speed,delay_servo);
//    delay(1);


//    LeftFront(6.2,8,2.5,fast_speed,delay_servo);
//    RightBack(6.2,8,2.5,fast_speed,delay_servo);
//    RightFront(6.2,8,2,fast_speed,delay_servo);
//    LeftBack(6.2,8,2,fast_speed,delay_servo);
//    delay(1);
//    RightFront(8,6.2,2.5,fast_speed,delay_servo);
//    LeftBack(8,6.2,2.5,fast_speed,delay_servo);
//    LeftFront(8,6.2,2,fast_speed,delay_servo);
//    RightBack(8,6.2,1.5,fast_speed,delay_servo);
//    delay(1);


    
//      RightFront(i,8,j, fast_speed, delay_servo);
//      LeftBack(i,8,j, fast_speed, delay_servo);
//      LeftFront(8,n,j, fast_speed, delay_servo);
//      RightBack(8,n,j, fast_speed, delay_servo);
//      delay(10);
//    LeftFront(i,8,j, fast_speed, delay_servo);
//    RightBack(i,8,j, fast_speed, delay_servo);
//    RightFront(8,n,j, fast_speed, delay_servo);
//    LeftBack(8,n,j, fast_speed, delay_servo);
//    delay(10);

//      trotBasicLeftward(100, 10);
////    trotBasicForward(200,20);
//    right_distance = scan(RIGHT);
//    writeLog(intToString(right_distance));
    /*
    int back_distance = scan(GRIP);
    while(back_distance <45){
      trotBasicForward(200,10);
      back_distance = scan(GRIP);
      writeLog(intToString(back_distance));
    }
    writeLog("TURNING RIGHT");
    int bearing = getBearing();
    for(int i=0; i<5; i++){
      //turning ~90 degree
      Serial.print("$CMP,");
      Serial.println(bearing);
      writeLog("CMP :");
      writeLog(intToString(bearing));
      enhancedTrotHigherRightTurn(200,10);
      delay(10);
      bearing = getBearing();
    }

    writeLog("SAVING VICTIM");
    pixy.setLamp(1,0);
    detectObject(1);
    gripMovement("pcg");
    delay(1000);
    gripMovement("lch");
    delay(1000);
    for(int i=0; i<=2; i++){
      trotBasicForward(100,10);
      delay(10);
    }
    initialPosition(200);
    delay(1000);
    gripMovement("lcg");
    pixy.setLamp(0,0);

    writeLog("SEQUENCES DONE");
    delay(10000000);
    */


    
    /* rotating
    Serial.println("Start L");
    int bearing = getBearing();
    for(int i=0; i<5; i++){
      //turning ~90 degree
      Serial.print("$CMP,");
      Serial.println(bearing);
      writeLog(intToString(bearing));
      enhancedTrotHigherLeftTurn(200,10);
      delay(10);
      bearing = getBearing();
    }
    Serial.print("$CMP,");
    Serial.println(bearing);
    Serial.println("END");
    delay(5000);
    
    Serial.println("StartR");
    bearing = getBearing();
    for(int i=0; i<5; i++){
      //turning ~90 degree
      Serial.print("$CMP,");
      Serial.println(bearing);
      writeLog(intToString(bearing));
      enhancedTrotHigherRightTurn(200,10);
      delay(10);
      bearing = getBearing();
    }
    Serial.print("$CMP,");
    Serial.println(bearing);
    Serial.println("END");
    delay(10000);
    */
    
//    trotBasicLeftward(120,10);
//    trotBasicRightward(120,10);
//    Serial.println(scan(GRIP));
//    long jarak = scan(GRIP);
//    if (jarak>1 && jarak<5){
//      jarak=scan(GRIP);
//      if (jarak>1 && jarak<5){
//        gripMovement("pcg");
//        Serial.println("_------------------------------------------------------_");
//        delay(1000);
//        gripMovement("lcg");
//      }
//    }
    



  /*  compass calibration  
  int calibrate = digitalRead(start_button);
  if(calibrate == HIGH){
    compassCalibration();
  }
*/

//    creepForward(300,1, 1);
//    creepForward(250, 5, 10);

    //puing
//    enhancedTrotHigherForward(300, 10);

//    trotBasicForward(200, 10);
//    trotBasicBackward(200, 10);
//    enhancedTrotHigherTurn(200, 10);
  }

  
  // while(true)
  // {
  //   for(int i=0; i<3; i++)
  //   {
  //     creepForward(150, 4, 10);
  //     delay(500);   
  //   }
  //   delay(500);
  //   for(int i=0; i<3; i++)
  //   {
  //     enhancedTrotForward(200);   
  //     delay(500);
  //   }
  //   delay(500);
  //   for(int i=0; i<3; i++)
  //   {
  //     enhancedTrotHigherForward(200, 10);  
  //     delay(500);
  //   }
  //   delay(500);
  //   for(int i=0; i<3; i++)
  //   {
  //     trotBasicBackward(200);  
  //     delay(500);
  //   }
  //   delay(500);
  // }
}
