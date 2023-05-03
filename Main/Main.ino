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
#define menu_button 2
#define start_button 11
//I2C address
#define CMPSAddress 0x60
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
#define TWO_BYTES 2


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

  while(true)
  {
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
    /*  Taking victim(s)  
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
    delay(1000000);
*/


  /*  compass calibration  
  int calibrate = digitalRead(start_button);
  if(calibrate == HIGH){
    compassCalibration();
  }
*/

//    creepForward(300,1, 1);
//    creepForward(250, 5, 10);
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
