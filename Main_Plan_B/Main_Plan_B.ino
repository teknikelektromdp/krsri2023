/*Libraries*/
#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Pixy2.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

/*Constants*/
//Menu
#define MENU_SIZE 3
//Button
#define menu_button 3
#define start_button 11
//I2C address
#define CMPS12Address 0x60
//Ultrasonic
#define RBD A0  //Right Back Diagonal
#define RFD A2  //Right Front Diagonal
#define LBD 9   //Left Back Diagonal
#define LFD 8   //Left Front Diagonal
#define GRIP A9   //Gripper
#define BACK 7    //Back
#define FRONT A8  //Front
#define LEFT_ A6  //Left
#define RIGHT 35   //Right
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
int coxa_set_angle = 30,
    femur_set_angle = 150,
    tibia_set_angle = 150;
int lastPositionLFX, lastPositionLFY, lastPositionLFZ,
    lastPositionLBX, lastPositionLBY, lastPositionLBZ,
    lastPositionRFX, lastPositionRFY, lastPositionRFZ,
    lastPositionRBX, lastPositionRBY, lastPositionRBZ;
double  x_default = 8, //(8),
        y_default = 8, //(8)
        z_default = 5; //5

/*Pixy*/
int left_min,
    left_max,
    right_min,
    right_max,
    front_min,
    front_max,
    lock,
    object1,
    object2;

/*COMPASS*/
int nReceived,
    _bearing;
int cmps_offset = 7,
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
int bearing;
/*Gyroscope*/
float gyrox = 0;
float gyroy = 0;
float gyroz = 0;
float _gyroScale = 1.0f / 16.f; // 1 Dps = 16 LSB

/* Data Logger */
const byte address[6] = "00001";

/* Ultrasonic */
int front_distance,
    left_distance,
    right_distance,
    back_distance,
    grip_distance,
    lfd_distance;

int mundur = 0,
    kanan = 0,
    kiri = 0,
    maju = 0,
    mod = 0,
    kondisiPitch=0;
int m1 = 1, trot_phase=1, mode=0;
int upper_pitch_limit = 4,  //(10)
    lower_pitch_limit = -4, //-3
    upper_roll_limit  = 4,  //3        10
    lower_roll_limit  = -4; //-3
int grip=0;
/*Classes*/
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
Pixy2 pixy;
RF24 radio(A7, A5); // CE, CSN

/*Gripper*/
Servo Gripper;

void(*resetFunc)(void) = 0;

void setup() {
  Serial.begin(9600);
  //Starting Dynamixel servo
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000, 2);
  initLogger();
  pinMode(menu_button, INPUT);
  pinMode(start_button, INPUT);
  attachInterrupt(digitalPinToInterrupt(menu_button), mainMenu, CHANGE);
  display.begin();
  display.setPowerSave(0);
  display.setFont(u8x8_font_pxplusibmcgathin_f);
  display.drawString(0, 0, "MDP Engine Bot");
  initPixy();
  Gripper.attach(A4);
  initGripper();
  initialPosition(400);
  delay(1000);
}

void loop()
{
//  Dynamixel.moveSpeed(7,500,150);
//  delay(10);
//  //femur
//  Dynamixel.moveSpeed(16,750,150);
//  delay(10);
//  //tibia
//  Dynamixel.moveSpeed(8,325,150);
//  moveGripper(17, 8, 3, 300);
  displayMenu();
//  gripMovement("lcg");
  pixy.setLamp(0, 0);
  int right_distance = scan(RIGHT),
      front_distance;

  int offsetkiri = 48, offsetkanan = 58;
  
  /*  
   *  testing purpose  
   *
  int kiri = 0;
  //  int bearing;
  //compassManualCalibration(50);
//  compassManualCalibration8bit(25);
//  int value=38;
//  compassManualCalibration8bit(value);
//  int mundur=1;
  while (true) {
//    Dynamixel.moveSpeed(7,500,250);
//    delay(300);
//    //tibia
////    Dynamixel.moveSpeed(8,100,250);
//    //femur
//    Dynamixel.moveSpeed(16,750,250);
//    delay(300);
//    //tibia
//    Dynamixel.moveSpeed(8,300,250);

//    Dynamixel.moveSpeed(16,675,150);
//    delay(10);
//    //tibia
//    Dynamixel.moveSpeed(8,350,150);
//    delay(500);
//    gripMovement("grip");
//    delay(1000);
//    initialPosition(400);
//    pixy.setLamp(1, 0);
//    
//    delay(300);
//    //tibia
//    Dynamixel.moveSpeed(8,100,250);
//    //femur
//    Dynamixel.moveSpeed(16,800,250);
//    Dynamixel.moveSpeed(7,620,250);
//    delay(300);
//    //tibia
//    Dynamixel.moveSpeed(8,225,250);
//    Gripper.write(120);
//
////    gripMovement("sog");
////    trotBasicBackward(100,10);
////    initialPosition(400);
//    standingPosition(3, 300);
//    delay(1000);
//    detectObject(2);
////    initialPosition(400);
//    int tibia_val=200, femur_val=800;
//    Dynamixel.moveSpeed(16,femur_val,250);
//    delay(300);
//    //tibia
//    Dynamixel.moveSpeed(8,tibia_val,250);
//    while(true){
//      Dynamixel.moveSpeed(16,300,50);
//      delay(300);
//      //tibia
//      Dynamixel.moveSpeed(8,700,75);
//      grip_distance=scan(GRIP);
//      display.clearDisplay();
//      display.setCursor(0,0);
//      display.print("distance=");
//      display.print(grip_distance);
//      display.display();
//      if(grip_distance<=8){
//        gripMovement("grip");
//        delay(3000);
//
//        //gripMovement("lcg");
//        //coxa
//        Dynamixel.moveSpeed(7,500,50);
//        delay(10);
//        //femur
//        Dynamixel.moveSpeed(16,200,50);
//        delay(10);
//        //tibia
//        Dynamixel.moveSpeed(8,300,50);
//        delay(10);
//        Gripper.write(150);
        while(true){
          pitchRoll();
          back_distance=scan(BACK);
          display.clearDisplay();
          display.setCursor(0,0);
          display.print("pitch=");
          display.print(pitch);
          
          display.setCursor(0,20);
          display.print("back=");
          display.print(back_distance);
          
          display.setCursor(0,10);
          display.print("roll=");
          display.print(roll);
          display.display();
//      if(femur_val<300 || tibia_val>700){
//        femur_val=800;
//        tibia_val=200;
//      }
//      else{
//        for(int i=0;i<10;i++){
//          tibia_val=tibia_val+1;
//        }
//        if(tibia_val%30==0){
//          for(int i=0; i<10; i++){
//            femur_val=femur_val-2;
//          }
//        }
//      }
    }
  }
  /* */



  //for(int i=0; i<5; i++){90 degree Left turn
  //      enhancedTrotHigherLeftTurn(500,10);
  //    }
  //  for(int i=0; i<5; i++){
  //    enhancedTrotHigherRightTurn(500,10);
  //  }
  //  delay(4000);
  //  initialPosition(200);
  //  delay(2000);


  //compassManualCalibration(45);
  int value=33;
  compassManualCalibration8bit(value);

  //starting from home
  while (true)
  {
    int k = 0, repositioning, bearing, home_ = 0;
    //bearing = getBearing();
    while (home_ == 0) {
      bearing = getBearing();
      if (bearing < front_r_offset && bearing > front_l_offset) {
        home_ = 1;
      }
      else if (bearing < front_l_offset || bearing > back_r_offset) {
        //        enhancedTrotLowerRightTurn(500,10);
        enhancedTrotHigherRightTurn(500, 10);
      }
      else if (bearing < back_l_offset && bearing > front_r_offset) {
        //        enhancedTrotLowerLeftTurn(500,10);
        enhancedTrotHigherLeftTurn(500, 10);
      }
      else {
        enhancedTrotHigherLeftTurn(500, 10);
      }
      delay(10);
    }
    
    //berjalan menuju korban pertama
    repositioning = 0;
    while (k == 0) {
      //berjalan kedepan korban pertama
      while (right_distance <= 50) {
        enhancedTrotHigherLeft(200,10);
        right_distance = scan(RIGHT);
      }
      //memperbaiki heading robot di depan robot
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing <= front_l_offset+3) {
          enhancedTrotLowerRightTurn(250, 10);
        }
        else if (bearing >= front_r_offset-3) {
          enhancedTrotLowerLeftTurn(250, 10);
        }
        else {
          repositioning = 1;
        }
      }

      right_distance = scan(RIGHT);
      if (right_distance > 50 && repositioning==1) {
        k=1;
      } else {
        k=0;
        repositioning=0;
      }
    }

    
    //menyesuaikan posisi pada saat di depan korban
    k=0;
    while(k==0){
      front_distance = scan(FRONT);
      while(front_distance>17){
        enhancedTrotHigherForward(150,3);
        front_distance = scan(FRONT);
      }
      //memperbaiki heading robot di depan korban
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing <= front_l_offset+3) {
          enhancedTrotLowerRightTurn(250, 10);
        }
        else if (bearing >= front_r_offset-3) {
          enhancedTrotLowerLeftTurn(250, 10);
        }
        else {
          repositioning = 1;
        }
      }
      front_distance = scan(FRONT);
      if (front_distance<=17 && repositioning==1) {
        k=1;
      } else {
        k=0;
        repositioning=0;
      }
    }

    //Taking victim(s)
//    writeLog("SAVING VICTIM");
    initialPosition(400);
    pixy.setLamp(1, 0);

    //mempersiapkan gripper untuk scanning
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,100,250);
    //femur
    Dynamixel.moveSpeed(16,800,250);
    Dynamixel.moveSpeed(7,620,250);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,250,250);
    Gripper.write(120);
    //mempersiapkan tubuh robot untuk scan dan pengambilan korban
    standingPosition(3, 200);
    delay(1000);
    //deteksi obyek
    detectObject(2);
//    initialPosition(400);

    //positioning gripper
    Dynamixel.moveSpeed(16,800,250);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,200,250);
    delay(500);
    //pengangkatan korban sembari mengambil korban
    Dynamixel.moveSpeed(16,300,50);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,700,75);
    //pencenkraman korban

    //apabila robot tidak berhasil mengcengkram korban, ??
    grip=0;
    while(grip==0){
      grip_distance=scan(GRIP);
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("distance=");
      display.print(grip_distance);
      display.display();
      if(grip_distance<=8){
        gripMovement("grip");
        delay(3000);
  
        //gripMovement("lcg");
        //coxa
        Dynamixel.moveSpeed(7,500,50);
        delay(10);
        //femur
        Dynamixel.moveSpeed(16,200,50);
        delay(10);
        //tibia
        Dynamixel.moveSpeed(8,300,50);
        delay(10);
        Gripper.write(150);
        grip=1;
      }
      else{
        grip=0;
      }
    }
    gripMovement("lcg");
    

    //jalan pecah
    
        
    //memasuki jalan pecah
    mundur = 0,
    kanan = 0,
    kiri = 0,
    maju = 0,
    mod = 0;
    m1 = 1, trot_phase=1, mode=0;
    while (trot_phase == 1 && mundur == 0 && maju==0) {
      enhancedTrotHigherLeft(600, 12);
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      bearing = getBearing();
      //acuan sedalam apa sudah memasuki rintangan jalan pecah
      //trigger untuk berubah metode gerak menjadi grip
      if(right_distance > 85){
        trot_phase=0;
      }
      //trigger untuk mengubah haluan gerak apabila robot tersangkut di rintangan dan berubah arah haluan
      if (bearing > right_direction - 25 && bearing < back_direction - 20) {
        mundur = 1;
      }
      //trigger untuk mengubah haluan gerak apabila robot tersangkut di rintangan dan berubah arah haluan
      if (bearing > left_direction) {
        maju = 1;
      }
    }

    
    //melewati rintangan jalan pecah
    mundur = 0;
    kanan  = 0;
    maju   = 0;
    mode   = 0;
    while (mode == 0){
      if (mundur == 1) {
        creepBackward(350, 4, 10);
      }
      else if (kanan == 1) {
        creepRight(300, 4, 10);
      }
      else if (maju == 1) {
        creepForward(300, 4, 10);
      }
      else{
        creepLeft(300, 4, 10);
      }
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      bearing = getBearing();
      pitchRoll();

      if (bearing > right_direction - 25 && bearing < back_direction - 20) {
        mundur = 1;
      }
      else{
        mundur=0;
      }

      if (bearing > left_direction) {
        maju = 1;
      }
      else{
        maju=0;
      }
      
      if (bearing > back_direction + 20 && bearing < left_direction - 20) {
        kanan = 1;
      }
      else{
        kanan = 0;
      }
      
      if(roll >= 12){
        mode=1;
      }
      else{
        mode=0;
      }
    }
    //jalan menurun
    mode=1;
    kondisiPitch=0;
    while(mode==1){
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      bearing = getBearing();
      pitchRoll();
      
      repositioning=0;
      while(repositioning==0){
        bearing = getBearing();
//        display.clearDisplay();
//        display.setCursor(10,10);
//        display.print(bearing);
//        display.display();
        if(bearing<right_l_offset){
          creepSlightRight(250,3,10);
        }
        else if(bearing>right_r_offset){
          creepSlightLeft(250,3,10);
        }
        else{
          repositioning=1;
        }
      }
      if (mundur == 1) {
        enhancedTrotHigherBackward(350,10);
      }
      else if (kanan == 1) {
        enhancedTrotHigherRight(350,10);
      }
      else if(maju == 1) {
        enhancedTrotHigherForward(350,10);
      }
      else{
        enhancedTrotHigherLeft(350,10);
      }
      
      if (bearing > right_direction - 25 && bearing < back_direction - 20) {
        mundur = 1;
      }
      else{
        mundur=0;
      }
      if (bearing > left_direction) {
        maju = 1;
      }
      else{
        maju=0;
      }
      
      if (bearing > back_direction + 20 && bearing < left_direction - 20) {
        kanan = 1;
      }
      else{
        kanan = 0;
      }
      if(pitch>=-84){
        kondisiPitch = kondisiPitch + 1;
      }
      if(back_distance<=30 && kondisiPitch>=1){
        mode=0;
      }
      else{
        mode=1;
      }
    }

    //persiapan sebelum meletakan korban 1
    k=0;
    repositioning=0;
    while(k==0){
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing <= back_l_offset+3) {
          enhancedTrotHigherRightTurn(300, 20);
        }
        else if (bearing >= back_r_offset-3) {
          enhancedTrotHigherLeftTurn(300, 20);
        }
        else {
          repositioning = 1;
        }
      }
      
      back_distance = scan(BACK);
      while(back_distance<30){
        enhancedTrotHigherForward(250,10);
        back_distance = scan(BACK);
      }
      //memperbaiki heading robot sebelum meletakkan korban pertama
      
      back_distance = scan(BACK);
      if (back_distance>=30 && repositioning==1) {
        k=1;
      } else {
        k=0;
        repositioning=0;
      }
    }

    Dynamixel.moveSpeed(16,800,100);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,200,100);
    Dynamixel.moveSpeed(7,620,100);
    delay(2000);
    
    gripMovement("open");
    delay(1000);
    gripMovement("lcg");
    
        
    //preparing for taking second victim
    k=0;
    repositioning = 0;
    while (k == 0) {
      //memperbaiki heading robot di depan robot
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing <= left_l_offset-10 && bearing >front_direction) {
          creepSlightRight(300,5,10);
        }
        else if (bearing >= left_r_offset-10 || bearing<=front_direction) {
          creepSlightLeft(300,5,10);
        }
        else {
          repositioning = 1;
          
        }
      }
      //berjalan kedepan korban kedua
      right_distance = scan(RIGHT);
      while (right_distance <= 50) {
        enhancedTrotHigherLeft(200,20);
        right_distance = scan(RIGHT);
      }
      delay(1000);
      right_distance = scan(RIGHT);
      if (right_distance > 50 && repositioning==1) {
        k=1;
      } else {
        k=0;
        repositioning=0;
      }
    }
    //mempersiapkan robot sebelum mengambil korban kedua
    k=0;
    while(k==0){
      front_distance = scan(FRONT);
      while(front_distance>17){
        enhancedTrotHigherForward(200,10);
        front_distance = scan(FRONT);
      }
      //memperbaiki heading robot di depan korban
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing <= left_l_offset-10 && bearing >front_direction) {
          creepSlightRight(250,4,10);
        }
        else if (bearing >= left_r_offset-10 || bearing<=front_direction) {
          creepSlightLeft(250,4,10);
        }
        else {
          repositioning = 1;
          
        }
      }
      front_distance = scan(FRONT);
      if (front_distance<=17 && repositioning==1) {
        k=1;
      } else {
        k=0;
        repositioning=0;
      }
    }

    initialPosition(400);
    pixy.setLamp(1, 0);

    //mempersiapkan gripper untuk scanning
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,100,250);
    //femur
    
    Gripper.write(120);

    
    //mempersiapkan tubuh robot untuk scan dan pengambilan korban
    standingPosition(6, 200);
    Dynamixel.moveSpeed(16,800,250);
    Dynamixel.moveSpeed(7,400,250);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,225,250);
    delay(1000);
    //deteksi obyek
    detectObject(3);
//    initialPosition(400);

    //positioning gripper
    Dynamixel.moveSpeed(16,800,250);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,225,250);
    delay(500);
    //pengangkatan korban sembari mengambil korban
    Dynamixel.moveSpeed(16,300,50);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,700,75);
    //pencenkraman korban

    grip=0;
    while(grip==0){
      grip_distance=scan(GRIP);
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("distance=");
      display.print(grip_distance);
      display.display();
      Serial.print("distance:");
      Serial.println(grip_distance);
      if(grip_distance<=18){
//        if(grip_distance<=9){
        gripMovement("grip");
        delay(3000);
  
        //gripMovement("lcg");
        //coxa
        Dynamixel.moveSpeed(7,500,50);
        delay(10);
        //femur
        Dynamixel.moveSpeed(16,200,125);
        delay(10);
        //tibia
        Dynamixel.moveSpeed(8,300,100);
        delay(10);
        Gripper.write(150);
        grip=1;
      }
      else{
        grip=0;
      }
    }
    
    //memperbaiki heading robot sebelum menuju safezone 2
    repositioning=0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing <= front_l_offset+10 || bearing>=left_l_offset-20) {
        creepSlightRight(250,5,10);
      }
      else if (bearing >= front_r_offset+10 && bearing <left_l_offset-20) {
        creepSlightLeft(250,5,10);
      }
      else {
        repositioning = 1;
      }
    }

    standingPosition(5,200);

    //putting second victim to safezone
    //tibia
    Dynamixel.moveSpeed(8,100,250);
    //femur
    Dynamixel.moveSpeed(16,800,250);
    Dynamixel.moveSpeed(7,400,250);
    delay(300);
    //tibia
    Dynamixel.moveSpeed(8,225,250);
    delay(500);
    gripMovement("open");
    delay(500);
    gripMovement("log");

    //memperbaiki heading robot sebelum keluar dari rintangan lumpur
    repositioning=0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing <= front_l_offset+20 || bearing>=left_l_offset-20) {
        enhancedTrotHigherRightTurn(300,10);
      }
      else if (bearing >= front_r_offset+20 && bearing <left_l_offset-20) {
        enhancedTrotHigherLeftTurn(300,10);
      }
      else {
        repositioning = 1;
      }
    }
    //keluar dari rintangan lumpur
    left_distance=scan(LEFT_);
    while(left_distance<60){
      enhancedTrotHigherRight(400, 20);
      left_distance=scan(LEFT_);
    }

    //membuat heading diantara celah
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < (front_l_offset+right_l_offset)/2) {
        enhancedTrotHigherRightTurn(300, 10);
      }
      else if (bearing > (front_r_offset+right_r_offset)/2) {
        enhancedTrotHigherLeftTurn(300, 10);
      }
      else {
        repositioning = 1;
      }
    }

    //mendekati rintangan jalan pecah kedua
    for(int i=0; i<3;i++){
      enhancedTrotHigherForward(400,10);
//      trotBasicForward(500,10);
    }

    //menghadap ke arah rintangan puing
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < right_l_offset) {
        enhancedTrotHigherRightTurn(300, 10);
      }
      else if (bearing > right_r_offset) {
        enhancedTrotHigherLeftTurn(300, 10);
      }
      else {
        repositioning = 1;
      }
    }
  
    left_distance=scan(LEFT_);
    while(left_distance>15){
      creepLeft(200,4,10);
      left_distance=scan(LEFT_);
    }
    
    while (true) {
      for(int i=0; i<3;i++){
        enhancedTrotHigherForward(400, 10);
      }
      for(int i=0; i<2;i++){
        creepForward(400,4,10);
      }
      
      front_distance = scan(FRONT);
      bearing = getBearing();
      if(bearing < right_l_offset-10 || bearing > right_r_offset+10){
        repositioning = 0;
      }
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing < right_l_offset-10) {
          creepSlightRight(250, 4, 10);
        }
        else if (bearing > right_r_offset+10) {
          creepSlightLeft(250, 4, 10);
        }
        else {
          repositioning = 1;
        }
      }
      front_distance = scan(FRONT);
      bearing = getBearing();
    }
    
    while(true);

    //old
    while (m1 == 1) {
      
      creepLeft(300, 4, 10);
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      bearing = getBearing();
      pitchRoll();
      
      if(mode==1){
        repositioning=0;
        while(repositioning==0){
          bearing = getBearing();
          display.clearDisplay();
          display.setCursor(10,10);
          display.print(bearing);
          display.display();
          if(bearing<right_l_offset){
            creepSlightRight(250,3,10);
          }
          else if(bearing>right_r_offset){
            creepSlightLeft(250,3,10);
          }
          else{
            repositioning=1;
          }
        }
      }
      
      if (bearing > right_direction - 25 && bearing < back_direction - 20) {
        mundur = 1;
      }
      
      if (bearing > left_direction) {
        maju = 1;
      }
      
      while (mundur == 1) {
//        enhancedTrotHigherBackward(750,9);
        if(mode==0){
          creepBackward(350, 4, 10);
        }
        else{
          enhancedTrotHigherBackward(350,10);
        }
        bearing = getBearing();
        pitchRoll();

        //condition when the robot facing the other side from taking the victim
        if (bearing > back_direction + 20 && bearing < left_direction - 20) {
          kanan = 1;
        }
        while (kanan == 1) {
//          enhancedTrotHigherRight(750,9);
          if(mode==0){
            creepRight(300, 4, 10);
          }
          else{
            enhancedTrotHigherRight(350,10);
          }
          back_distance = scan(BACK);
          left_distance = scan(LEFT_);
          right_distance = scan(RIGHT);
          front_distance = scan(FRONT);
          bearing = getBearing();
          pitchRoll();
          
          //condition when the robot heading is turning right or the front of the robot is facing toward r4
          if (bearing > left_direction-25) {
            maju = 1;
            kanan = 0;
            mundur = 0;
          }
          if (front_distance > 30 && right_distance < 45) {
            initialPosition(400);
            delay(250);
            pitchRoll();
            lcdDisplay();
            if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
              initialPosition(300);
              kanan = 0;
              mundur = 0;
              m1 = 0;
            }
          }
        }

        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();
        
          if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
            initialPosition(400);
            mundur = 0;
            m1 = 0;
          }
        }
        if (bearing > (front_l_offset - 10) && bearing < (front_r_offset - 10)) {
          mundur = 0;
        }
      }

      while (maju == 1) {
        if(mode==0){
          creepForward(300, 4, 10);
        }
        else{
          enhancedTrotHigherForward(350,10);
        }
        bearing = getBearing();
        pitchRoll();

        //condition when the robot facing the other side from taking the victim
        if (bearing > back_direction - 20 && bearing < left_direction - 20) {
          kanan = 1;
          maju = 0;
        }
        if (bearing < front_direction+20){
          maju=0;
        }

        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();
        
//        if ((left_distance > 50 && left_distance < 150) && (front_distance <= 35 && front_distance > 0)) {
        if ((left_distance > 30) && (front_distance <= 45)) {
          initialPosition(400);
          delay(250);
          pitchRoll();
          lcdDisplay();
          
          if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
            initialPosition(400);
            maju = 0;
            m1 = 0;
          }
        }
      }
      while (kanan == 1) {
//          enhancedTrotHigherRight(750,9);
        if(mode=0){
          creepRight(300, 4, 10);
        }
        else{
          enhancedTrotHigherRight(350,10);
        }
        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();

        //condition when the robot heading is turning right or the front of the robot is facing toward r4
        if (bearing > left_direction) {
          maju = 1;
          kanan = 0;
        }
        
        if(front_distance > 30 && right_distance < 45){
          initialPosition(400);
          delay(250);
          pitchRoll();
          lcdDisplay();
          if((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)){
            initialPosition(300);
            kanan = 0;
            mundur = 0;
            maju=0;
            m1 = 0;
          }
        }
      }

      back_distance = scan(BACK);
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      bearing = getBearing();
      pitchRoll();
      
      if(roll >= 12){
        mode=1;
      }
      if ((back_distance > 30) && (left_distance < 45)) {
        initialPosition(600);
        delay(200);
        pitchRoll();
        if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
          m1 = 0;
        }
      }

    
    while(true);
    delay(200);
    gripMovement("take");
    
    delay(500);
    gripMovement("lcg");
    
//    front_distance = scan(FRONT);
//    while (front_distance > 12) {
//      enhancedTrotHigherForward(250,10);
//      front_distance = scan(FRONT);
//    }
    pixy.setLamp(0, 0);
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < front_l_offset) {
        enhancedTrotLowerRightTurn(250, 10);
      }
      else if (bearing > front_r_offset) {
        enhancedTrotLowerLeftTurn(250, 10);
      }
      else {
        repositioning = 1;
      }
    }

    delay(100);
    initialPosition(200);
    delay(100);

    /*  descending the track (obstacle m1)  */
//    int mundur = 0,
//        kanan = 0,
//        kiri = 0,
//        maju = 0,
//        mod = 0;
//    pitchRoll();
//    int m1 = 1, trot_phase=1, mode=0;
//    int upper_pitch_limit = 4,  //(10)
//        lower_pitch_limit = -4, //-3
//        upper_roll_limit  = 4,  //3        10
//        lower_roll_limit  = -4; //-3


//    while(m1==1){
//      for(int i=0; i<3;i++){
//        enhancedTrotHigherLeft(400, 10);
//      }
//      creepLeft(400,4,10);
//      if(roll >= 12){
//        mode=1;
//      }
//      if ((back_distance > 30) && (left_distance < 45)) {
//        initialPosition(600);
//        delay(200);
//        pitchRoll();
//        if ((pitch <= upper_pitch_limit || pitch >= lower_pitch_limit) && (roll <= upper_roll_limit || roll >= lower_roll_limit)) {
//          m1 = 0;
//        }
//      }
//      if(mode==1){
//        repositioning=0;
//        while(repositioning==0){
//          bearing = getBearing();
//          display.clearDisplay();
//          display.setCursor(10,10);
//          display.print(bearing);
//          display.display();
//          if(bearing<right_l_offset){
//            creepSlightRight(250,3,10);
//          }
//          else if(bearing>right_r_offset){
//            creepSlightLeft(250,3,10);
//          }
//          else{
//            repositioning=1;
//          }
//        }
//        mundur=1;
//      }
//      while (mundur == 1) {
//        if(mode==0){
//          creepBackward(300, 4, 10);
//        }
//        else{
//          enhancedTrotHigherBackward(350,10);
//        }
//        bearing = getBearing();
//        pitchRoll();
//        if (right_distance > 30 && back_distance <= 45){
//          initialPosition(400);
//          delay(250);
//          pitchRoll();
//          lcdDisplay();
//          if ((pitch <= upper_pitch_limit || pitch >= lower_pitch_limit) && (roll <= upper_roll_limit || roll >= lower_roll_limit)) {
//            initialPosition(400);
//            mundur = 0;
//            m1 = 0;
//          }
//        }
//      }
//      
//    }
    ///* before*/
    while (m1 == 1) {
      right_distance = scan(RIGHT);
      while (trot_phase == 1 && mundur == 0 && maju==0) {
        enhancedTrotHigherLeft(600, 12);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        back_distance = scan(BACK);
        bearing = getBearing();
        if(right_distance > 85){
          trot_phase=0;
        }
        if (bearing > right_direction - 25 && bearing < back_direction - 20) {
          mundur = 1;
        }
        if (bearing > left_direction) {
          maju = 1;
        }
      }
      
      creepLeft(300, 4, 10);
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      bearing = getBearing();
      pitchRoll();
      
      if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);

      if(mode==1){
        repositioning=0;
        while(repositioning==0){
          bearing = getBearing();
          display.clearDisplay();
          display.setCursor(10,10);
          display.print(bearing);
          display.display();
          if(bearing<right_l_offset){
            creepSlightRight(250,3,10);
          }
          else if(bearing>right_r_offset){
            creepSlightLeft(250,3,10);
          }
          else{
            repositioning=1;
          }
        }
      }
      
//      if ((back_distance > 50 && back_distance < 150) && (left_distance < 25)) {
      

      if (bearing > right_direction - 25 && bearing < back_direction - 20) {
        mundur = 1;
      }
      
      if (bearing > left_direction) {
        maju = 1;
      }
      
      while (mundur == 1) {
//        enhancedTrotHigherBackward(750,9);
        if(mode==0){
          creepBackward(350, 4, 10);
        }
        else{
          enhancedTrotHigherBackward(350,10);
        }
        bearing = getBearing();
        pitchRoll();

        //condition when the robot facing the other side from taking the victim
        if (bearing > back_direction + 20 && bearing < left_direction - 20) {
          kanan = 1;
        }
        while (kanan == 1) {
//          enhancedTrotHigherRight(750,9);
          if(mode==0){
            creepRight(300, 4, 10);
          }
          else{
            enhancedTrotHigherRight(350,10);
          }
          back_distance = scan(BACK);
          left_distance = scan(LEFT_);
          right_distance = scan(RIGHT);
          front_distance = scan(FRONT);
          bearing = getBearing();
          pitchRoll();
          if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);
          //condition when the robot heading is turning right or the front of the robot is facing toward r4
          if (bearing > left_direction-25) {
            maju = 1;
            kanan = 0;
            mundur = 0;
          }
          if (front_distance > 30 && right_distance < 45) {
            initialPosition(400);
            delay(250);
            pitchRoll();
            lcdDisplay();
            if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
              initialPosition(300);
              kanan = 0;
              mundur = 0;
              m1 = 0;
            }
          }
        }

        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();
        if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);
        display.display();
//        if ((right_distance > 50 && right_distance < 150) && (back_distance <= 35 && back_distance > 0)){
        if (right_distance > 30 && back_distance <= 45){
          initialPosition(600);
          delay(250);
          pitchRoll();
          display.clearDisplay();
          display.setCursor(0,0);
          display.print("pit=");  display.print(pitch);
          display.setCursor(8,0);
          display.print("ro=");   display.print(roll);
          display.setCursor(0,10);
          display.print("cmps=");   display.print(bearing);
          display.setCursor(8,10);
          display.print("mod=");   display.print(mod);
          display.setCursor(0,20);
          display.print("b=");      display.print(back_distance);
          display.setCursor(8,20);
          display.print("r=");      display.print(right_distance);
          display.setCursor(0,30);
          display.print("f=");      display.print(front_distance);
          display.setCursor(8,30);
          display.print("l=");      display.print(left_distance);
          display.display();
          if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
            initialPosition(400);
            mundur = 0;
            m1 = 0;
          }
        }
        if (bearing > (front_l_offset - 10) && bearing < (front_r_offset - 10)) {
          mundur = 0;
        }
      }

      while (maju == 1) {
        if(mode==0){
          creepForward(300, 4, 10);
        }
        else{
          enhancedTrotHigherForward(350,10);
        }
        bearing = getBearing();
        pitchRoll();

        //condition when the robot facing the other side from taking the victim
        if (bearing > back_direction - 20 && bearing < left_direction - 20) {
          kanan = 1;
          maju = 0;
        }
        if (bearing < front_direction+20){
          maju=0;
        }

        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();
        if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);
//        if ((left_distance > 50 && left_distance < 150) && (front_distance <= 35 && front_distance > 0)) {
        if ((left_distance > 30) && (front_distance <= 45)) {
          initialPosition(400);
          delay(250);
          pitchRoll();
          lcdDisplay();
          
          if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
            initialPosition(400);
            maju = 0;
            m1 = 0;
          }
        }
      }
      while (kanan == 1) {
//          enhancedTrotHigherRight(750,9);
        if(mode=0){
          creepRight(300, 4, 10);
        }
        else{
          enhancedTrotHigherRight(350,10);
        }
        back_distance = scan(BACK);
        left_distance = scan(LEFT_);
        right_distance = scan(RIGHT);
        front_distance = scan(FRONT);
        bearing = getBearing();
        pitchRoll();

        //condition when the robot heading is turning right or the front of the robot is facing toward r4
        if (bearing > left_direction) {
          maju = 1;
          kanan = 0;
        }
        
        if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);
        if(front_distance > 30 && right_distance < 45){
          initialPosition(400);
          delay(250);
          pitchRoll();
          lcdDisplay();
          if((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)){
            initialPosition(300);
            kanan = 0;
            mundur = 0;
            maju=0;
            m1 = 0;
          }
        }
      }

      back_distance = scan(BACK);
      left_distance = scan(LEFT_);
      right_distance = scan(RIGHT);
      front_distance = scan(FRONT);
      bearing = getBearing();
      pitchRoll();
      if(maju==1){
          mod=1;
        }
        else if(kanan==1){
          mod=2;
        }
        else if(mundur==1){
          mod=3;
        }
        else if(kiri==1){
          mod=5;
        }
        else {
          mod=10;
        }
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("pit=");  display.print(pitch);
        display.setCursor(8,0);
        display.print("ro=");   display.print(roll);
        display.setCursor(0,10);
        display.print("cmps=");   display.print(bearing);
        display.setCursor(8,10);
        display.print("mod=");   display.print(mod);
        display.setCursor(0,20);
        display.print("b=");      display.print(back_distance);
        display.setCursor(8,20);
        display.print("r=");      display.print(right_distance);
        display.setCursor(0,30);
        display.print("f=");      display.print(front_distance);
        display.setCursor(8,30);
        display.print("l=");      display.print(left_distance);
      if(roll >= 12){
        mode=1;
      }
      if ((back_distance > 30) && (left_distance < 45)) {
        initialPosition(600);
        delay(200);
        pitchRoll();
        if ((pitch <= upper_pitch_limit && pitch >= lower_pitch_limit) && (roll <= upper_roll_limit && roll >= lower_roll_limit)) {
          m1 = 0;
        }
      }
    }

    pixy.setLamp(1, 1);
    
    /*  first algorithm to put the victim
      repositioning=0;
      while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(10,10);
      display.print(bearing);
      display.display();
      if(bearing<back_l_offset){
        enhancedTrotHigherRightTurn(400,10);
      }
      else if(bearing>back_r_offset){
        enhancedTrotHigherLeftTurn(400,10);
      }
      else{
        repositioning=1;
      }
      }
      initialPosition(400);
      ////////////////////////////////////////////////////////repositioning on r4 before rotating to put the victim
      //    fr

      ////////////////////////////////////////////////////////
      pixy.setLamp(0,0);
      repositioning=0;
      while(repositioning==0){
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(10,10);
      display.print(bearing);
      display.display();
      if(bearing<((back_l_offset+right_l_offset)/2)-15){
        enhancedTrotHigherRightTurn(400,10);
      }
      else if(bearing>((back_r_offset+right_r_offset)/2)-15){
        enhancedTrotHigherLeftTurn(400,10);
      }
      else{
        repositioning=1;
      }
      }
    */
//    pixy.setLamp(0,1);
    /*
    back_distance = scan(BACK);
    left_distance = scan(LEFT_);
    right_distance = scan(RIGHT);
    front_distance = scan(FRONT);
    bearing = getBearing();
    pitchRoll();
    if(mode==0){
      int step_number = 6;
      if(bearing < front_r_offset+22 && bearing > front_l_offset-22){
        if(front_distance>20){
          for(int i=0; i<step_number; i++){
            creepForward(400,4,10);
          }
        }
      }
      else if(bearing < left_r_offset+22 && bearing > left_l_offset-22){
        if(right_distance>20){
          for(int i=0; i<step_number; i++){
            creepRight(400,4,10);
          }
        }
      }
      else if(bearing < back_r_offset+22 && bearing > back_l_offset-22){
        if(back_distance>20){
          for(int i=0; i<step_number; i++){
            creepBackward(400,4,10);
          }
        }
      }
      else if(bearing < right_r_offset+22 && bearing > right_l_offset-22){
        if(left_distance>20){
          for(int i=0; i<step_number; i++){
            creepLeft(400,4,10);
          }
        }
      }
      else{
        if(front_distance>20){
          for(int i=0; i<step_number; i++){
            creepForward(400,4,10);
          }
        }
      }
    }
    else if (mode==1){
      if(left_distance>15){
        for(int i=0; i<2; i++){
          creepLeft(400,4,10);
        }
      }
    }
    else{
    
    }
    */
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    pixy.setLamp(1,0);
    back_distance = scan(BACK);
    left_distance = scan(LEFT_);
    right_distance = scan(RIGHT);
    front_distance = scan(FRONT);
    bearing = getBearing();
    pitchRoll();
    
    /*  second algorithm to put the victim  
    int r4 = 1;
    if(back_distance <= 45 && bearing < ((back_r_offset + right_r_offset) / 2) - 10 && bearing > ((back_l_offset + right_l_offset) / 2) - 10){
      r4 = 0;
    }
    while(r4 == 1){
//      pixy.setLamp(0,0);
      int repositioning = 0;
      while(repositioning == 0){
        bearing = getBearing();
        if(bearing < ((back_l_offset + right_l_offset) / 2) - 8){
          enhancedTrotHigherRightTurn(400, 10);
//          enhancedTrotLowerRightTurn(600, 10);
        }
        else if(bearing > ((back_r_offset + right_r_offset) / 2) - 12){
          enhancedTrotHigherLeftTurn(400, 10);
//          enhancedTrotLowerLeftTurn(600, 10);
        }
        else {
          repositioning = 1;
        }
      }

      bearing = getBearing();
      if(bearing < ((back_r_offset + right_r_offset) / 2) - 12 && bearing > ((back_l_offset + right_l_offset) / 2) - 8){
        r4 = 0;
      }
    }
    pixy.setLamp(0,0);
    back_distance=scan(BACK);
    if(back_distance<20){
      for(int i=0; i<2;i++){
        trotBasicForward(300,10);
      }
    }
    else{
      trotBasicForward(200,10);
    }
    
    */

    
    /* Putting Victim 
    delay(200);
    gripMovement("pcg");
    delay(200);
    gripMovement("pog");
    delay(200);
    gripMovement("log");
    delay(600);
    for(int i=0; i<2; i++){
//      trotBasicForward(200,10);
      enhancedTrotHigherForward(300,10);
    }
*/
    left_distance=scan(LEFT_);
    back_distance=scan(BACK);
    if(back_distance>20 && left_distance<20){
      initialPosition(300);
      left_distance=scan(LEFT_);
      back_distance=scan(BACK);
      back_distance=back_distance-20;
      left_distance=left_distance-10;
      moveGripper(left_distance, back_distance, 3, 300);
      delay(5000);
      gripMovement("open");
    }
    else{
      int r4 = 1;
      if(back_distance <= 45 && bearing < ((back_r_offset + right_r_offset) / 2) - 10 && bearing > ((back_l_offset + right_l_offset) / 2) - 10){
        r4 = 0;
      }
      while(r4 == 1){
  //      pixy.setLamp(0,0);
        int repositioning = 0;
        while(repositioning == 0){
          bearing = getBearing();
          if(bearing < ((back_l_offset + right_l_offset) / 2) - 8){
            enhancedTrotHigherRightTurn(400, 10);
  //          enhancedTrotLowerRightTurn(600, 10);
          }
          else if(bearing > ((back_r_offset + right_r_offset) / 2) - 12){
            enhancedTrotHigherLeftTurn(400, 10);
  //          enhancedTrotLowerLeftTurn(600, 10);
          }
          else {
            repositioning = 1;
          }
        }
  
        bearing = getBearing();
        if(bearing < ((back_r_offset + right_r_offset) / 2) - 12 && bearing > ((back_l_offset + right_l_offset) / 2) - 8){
          r4 = 0;
        }
      }
      Dynamixel.moveSpeed(7,520,150);
      delay(10);
      //femur
      Dynamixel.moveSpeed(16,800,150);
      delay(10);
      //tibia
      Dynamixel.moveSpeed(8,200,150);
      delay(5000);
      gripMovement("open");
    }
    while(true);
    /*  Robot muddy field  */
    int r5 = 1;
    while(r5 == 1){
      pixy.setLamp(0, 0);
      int repositioning = 0;
      while(repositioning == 0){
        bearing = getBearing();
        if(bearing < back_l_offset){
//          enhancedTrotHigherRightTurn(400, 10);
          enhancedTrotLowerRightTurn(400, 10);
        }
        else if(bearing > back_r_offset){
//          enhancedTrotHigherLeftTurn(400, 10);
          enhancedTrotLowerLeftTurn(400, 10);
        }
        else{
          repositioning = 1;
        }
      }
      for(int i=0; i<2;i++){
        trotBasicRightward(200,10);
      }
      repositioning = 0;
      while(repositioning == 0){
        bearing = getBearing();
        if(bearing < back_l_offset){
//          enhancedTrotHigherRightTurn(400, 10);
          enhancedTrotLowerRightTurn(400, 10);
        }
        else if(bearing > back_r_offset){
//          enhancedTrotHigherLeftTurn(400, 10);
          enhancedTrotLowerLeftTurn(400, 10);
        }
        else{
          repositioning = 1;
        }
      }

      int maju = 1;
      front_distance = scan(FRONT);
      back_distance = scan(BACK);
      while (maju == 1) {

        enhancedTrotHigherForward(300, 10);
        front_distance = scan(FRONT);
        back_distance = scan(BACK);
        if (back_distance > 48 && front_distance < 60) {
//          front_distance = scan(FRONT);
////          while((front_distance>=35 ||front_distance==0)  && maju==1){
//          while(front_distance>35 && back_distance<70){
//            creepForward(300,4,10);
//            back_distance = scan(BACK);
//            left_distance = scan(LEFT_);
//            right_distance = scan(RIGHT);
//            front_distance = scan(FRONT);
//            bearing = getBearing();
//            pitchRoll();
//            if(bearing < back_l_offset || bearing > back_r_offset){
//              repositioning = 0;
//            }
//            while (repositioning == 0) {
//              bearing = getBearing();
//              display.clearDisplay();
//              display.setCursor(5, 5);
//              display.print(bearing);
//              display.display();
//              if (bearing < back_l_offset-2) {
////                enhancedTrotHigherRightTurn(250, 10);
//                creepSlightRight(250, 4, 10);
//              }
//              else if (bearing > back_r_offset+2) {
////                enhancedTrotHigherLeftTurn(250, 10);
//                creepSlightLeft(250, 4, 10);
//              }
//              else {
//                repositioning = 1;
//              }
//            }
//            back_distance = scan(BACK);
//            left_distance = scan(LEFT_);
//            right_distance = scan(RIGHT);
//            front_distance = scan(FRONT);
//            bearing = getBearing();
//            pitchRoll();

//          }
          for (int i = 0; i < 3; i++) {
            creepForward(200, 4, 10);
          }
          initialPosition(200);
          delay(300);
          int repositioning = 0;
          while (repositioning == 0) {
            bearing = getBearing();
//            if (bearing < (left_l_offset - 27) && bearing >front_r_offset) {FOR I= 5
            if (bearing < (left_l_offset - 20) && bearing >front_r_offset) {//for i=3
//              enhancedTrotHigherRightTurn(200, 10);
              creepSlightRight(250, 4, 10);
            }
//            else if (bearing > (left_r_offset - 27) || bearing<=front_r_offset) {FOR I=5
            else if (bearing > (left_r_offset - 20) || bearing<=front_r_offset) {//for i=3
//              enhancedTrotHigherLeftTurn(200, 10);
              creepSlightLeft(250, 4, 10);
            }
            else {
              repositioning = 1;
            }
          }
          gripMovement("loh");
          for (int i = 0; i < 6; i++) {
            if (i == 4) {
              gripMovement("pog");
            }
            creepBackward(200, 5, 10);
          }
          delay(500);
          gripMovement("pog");
          delay(300);
          gripMovement("pcg");
          delay(200);
          gripMovement("lcg");
          delay(200);
//          for (int i = 0; i < 4; i++) {
//            if(i==1){
//              gripMovement("lcg");
//            }
            creepForward(200, 4, 10);
//          }


///////////////////////////////////////////going to second safezone
          compassManualCalibration8bit(value-10);

/*
//          
//          left_distance = scan(LEFT_);
//          while (left_distance > 14) {
//            creepLeft(200, 4, 10);
//            back_distance = scan(BACK);
//            left_distance = scan(LEFT_);
//            right_distance = scan(RIGHT);
//            front_distance = scan(FRONT);
//            bearing = getBearing();
//            pitchRoll();
//            if(bearing < left_l_offset || bearing > left_r_offset){
//              repositioning = 0;
//            }
//            while (repositioning == 0) {
//              bearing = getBearing();
//              display.clearDisplay();
//              display.setCursor(5, 5);
//              display.print(bearing);
//              display.display();
//              if (bearing < left_l_offset) {
////                enhancedTrotHigherRightTurn(250, 10);
//                creepSlightRight(250, 4, 10);
//              }
//              else if (bearing > left_r_offset) {
////                enhancedTrotHigherLeftTurn(250, 10);
//                creepSlightLeft(250, 4, 10);
//              }
//              else {
//                repositioning = 1;
//              }
//            }
//            back_distance = scan(BACK);
//            left_distance = scan(LEFT_);
//            right_distance = scan(RIGHT);
//            front_distance = scan(FRONT);
//            bearing = getBearing();
//            pitchRoll();
//          }
*/

//          for(int i=0; i<5;i++){
//            creepLeft(200, 4, 10);
//          }
          
          
          repositioning = 0;
          while (repositioning == 0) {
            bearing = getBearing();
            display.clearDisplay();
            display.setCursor(5, 5);
            display.print(bearing);
            display.display();
            if (bearing < right_l_offset || bearing >= left_direction-27) {
//              enhancedTrotHigherRightTurn(250, 10);
//              creepSlightRight(250, 4, 10);
              creepSlightRight(600, 4, 10);
            }
            else if (bearing > right_r_offset && bearing < left_direction-27) {
//              enhancedTrotHigherLeftTurn(250, 10);
//              creepSlightLeft(250, 4, 10);
              creepSlightLeft(600, 4, 10);
            }
            else {
              repositioning = 1;
            }
          }

          right_distance = scan(RIGHT);
          while (right_distance > 14) {
            creepRight(200, 4, 10);
            back_distance = scan(BACK);
            left_distance = scan(LEFT_);
            right_distance = scan(RIGHT);
            front_distance = scan(FRONT);
            bearing = getBearing();
            pitchRoll();
            if(bearing < right_l_offset || bearing > right_r_offset){
              repositioning = 0;
            }
            while (repositioning == 0) {
              bearing = getBearing();
              display.clearDisplay();
              display.setCursor(5, 5);
              display.print(bearing);
              display.display();
              if (bearing < right_l_offset) {
//                enhancedTrotHigherRightTurn(250, 10);
                creepSlightRight(250, 4, 10);
              }
              else if (bearing > right_r_offset) {
//                enhancedTrotHigherLeftTurn(250, 10);
                creepSlightLeft(250, 4, 10);
              }
              else {
                repositioning = 1;
              }
            }
            back_distance = scan(BACK);
            left_distance = scan(LEFT_);
            right_distance = scan(RIGHT);
            front_distance = scan(FRONT);
            bearing = getBearing();
            pitchRoll();
          }

          
          back_distance = scan(BACK);
          while (back_distance < 22 || back_distance > 30) {
            if(back_distance < 22){
              enhancedTrotHigherForward(400, 10);
            }
            if(back_distance > 30){
              enhancedTrotHigherBackward(400, 10);
            }
//          creepForward(400, 4, 10);
            back_distance = scan(BACK);
          }
          
          /////////////////////////////////////////////////////////////////////////putting second victim
          repositioning = 0;
          while (repositioning == 0) {
            bearing = getBearing();
            display.clearDisplay();
            display.setCursor(5, 5);
            display.print(bearing);
            display.display();
            if (bearing < right_l_offset - 30) {
//              enhancedTrotHigherRightTurn(250, 10);
              creepSlightRight(250, 4, 10);
            }
            else if (bearing > right_r_offset - 30) {
//              enhancedTrotHigherLeftTurn(250, 10);
              creepSlightLeft(250, 4, 10);
            }
            else {
              repositioning = 1;
            }
          }
          delay(200);
          gripMovement("pcg");
          delay(200);
          gripMovement("pog");
          delay(200);
          gripMovement("log");
          delay(200);
          gripMovement("lcg");
          delay(200);
          maju = 0;
          r5 = 0;
        }
      }
      initialPosition(500);
    }
    
    /*  clearing r5(marbles) and approaching r6  */
    //recalibrating robot facing
    compassManualCalibration8bit(value-13);
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < right_l_offset) {
  //        enhancedTrotHigherRightTurn(250, 10);
        creepSlightRight(250, 4, 10);
        
      }
      else if (bearing > right_r_offset) {
  //        enhancedTrotHigherLeftTurn(250, 10);
        creepSlightLeft(250, 4, 10);
      }
      else {
        repositioning = 1;
      }
    }
    /*  clearing r5(marbles) and approaching r6  */
    //recalibrating robot facing
//    compassManualCalibration8bit(25);
    int interlude = 1;
    while(interlude == 1){
      creepForward(300,5,10);
  
      back_distance = scan(BACK);
      bearing = getBearing();
  
      if(bearing > right_l_offset || bearing < right_r_offset){
        repositioning = 0;
        while (repositioning == 0) {
          bearing = getBearing();
          display.clearDisplay();
          display.setCursor(5, 5);
          display.print(bearing);
          display.display();
          if (bearing < right_l_offset) {
            enhancedTrotHigherRightTurn(250, 10);
          }
          else if (bearing > right_r_offset) {
            enhancedTrotHigherLeftTurn(250, 10);
          }
          else {
            repositioning = 1;
          }
        }
      }
      back_distance = scan(BACK);
      bearing = getBearing();
      if(back_distance > 55){
        interlude=0;
      }
    }
    initialPosition(400);
  
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < (front_l_offset+right_l_offset)/2) {
        enhancedTrotHigherRightTurn(300, 10);
      }
      else if (bearing > (front_r_offset+right_r_offset)/2) {
        enhancedTrotHigherLeftTurn(300, 10);
      }
      else {
        repositioning = 1;
      }
    }
  
    for(int i=0; i<3;i++){
      enhancedTrotHigherForward(400,10);
//      trotBasicForward(500,10);
    }
  
    bearing = getBearing();
  
    repositioning = 0;
    while (repositioning == 0) {
      bearing = getBearing();
      display.clearDisplay();
      display.setCursor(5, 5);
      display.print(bearing);
      display.display();
      if (bearing < right_l_offset) {
        enhancedTrotHigherRightTurn(300, 10);
  //        creepSlightRight(250, 4, 10);
      }
      else if (bearing > right_r_offset) {
        enhancedTrotHigherLeftTurn(300, 10);
  //        creepSlightLeft(250, 4, 10);
      }
      else {
        repositioning = 1;
      }
    }
    
    for(int i=0; i<2; i++){
      creepLeft(200,4,10);
    }
    
    front_distance = scan(FRONT);
    while (true) {
//      if(front_distance<70){
//        creepForward(450,4,10);
//      }
//      
//      else{
//        for(int i=0; i<2;i++){
//          enhancedTrotHigherForward(600, 12);
//        }
//      }
      for(int i=0; i<3;i++){
        enhancedTrotHigherForward(400, 10);
      }
      creepForward(400,4,10);
      front_distance = scan(FRONT);
      bearing = getBearing();
      if(bearing < right_l_offset-10 || bearing > right_r_offset+10){
        repositioning = 0;
      }
      while (repositioning == 0) {
        bearing = getBearing();
        display.clearDisplay();
        display.setCursor(5, 5);
        display.print(bearing);
        display.display();
        if (bearing < right_l_offset-10) {
  //                enhancedTrotHigherRightTurn(250, 10);
          creepSlightRight(250, 4, 10);
        }
        else if (bearing > right_r_offset+10) {
  //                enhancedTrotHigherLeftTurn(250, 10);
          creepSlightLeft(250, 4, 10);
        }
        else {
          repositioning = 1;
        }
      }
      front_distance = scan(FRONT);
      bearing = getBearing();
    }
  }
}
