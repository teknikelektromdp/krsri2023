/*Libraries*/
#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Pixy2.h>

/*Constants*/
//Menu
#define MENU_SIZE 3
//Button
#define menu_button 3
#define start_button 6
//Ultrasonic
#define RBD A0 //Right Back Diagonal
#define RFD A2 //Right Front Diagonal
#define LBD 9 //Left Back Diagonal
#define LFD 8 //Left Front Diagonal
#define GRIP A9 //Gripper
#define FRONT A8//Front
#define LEFT_ A6//Left
#define RIGHT A4//Right


/*Push buttons + Menu*/
int menuState = LOW,
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

/*Classes*/
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
Pixy2 pixy;

void(*resetFunc)(void)=0;

void setup() 
{
  Serial.begin(9600);
  //Starting Dynamixel servo
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  pinMode(menu_button, INPUT);
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
  // displayMenu();
//  getObjectLocation()
  gripMovement("scg");
  while(true)
  {
    
    Serial.println(scan(GRIP));
    long jarak = scan(GRIP);
    if (jarak>1 && jarak<5){
      jarak=scan(GRIP);
      if (jarak>1 && jarak<5){
        gripMovement("pcg");
        Serial.println("_------------------------------------------------------_");
      }
    }
//    detectObject(1);
//    gripMovement("pcg");
//    gripMovement("pcg");
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
