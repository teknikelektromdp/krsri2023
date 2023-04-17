//x = 12,5 cm
//y = 12,5 cm

#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define button_pin1 6
#define button_pin2 11
#define LED_pin 10

int button_state=0;

int coxa_set_angle=30,
    femur_set_angle=150,
    tibia_set_angle=150;
    
int servo_delay = 1;
int servo_speed = 750;

int button =0;

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
  
void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  //Starting LCD
  display.setTextSize(1); 
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,10);
  display.println("Start");
  display.display();
  //Starting Dynamixel servo
  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000,15);
  //setting up push button
  pinMode(button_pin1, INPUT);
  pinMode(LED_pin, OUTPUT);
  delay(1000);
  display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  int starting_x=8/*last working value(=8)*/, starting_z=5,//last try(=4)
      desired_x =5/*last working value(=5)*/, desired_z =3,//last try(=1)
      starting_y=8/*last try(=8)*/, test_desired_y=5,//only for testing, since when using 5 for x value it only make the robot move backward
      delay_servo=1;
  double  x_increment=(double)(starting_x-desired_x)/5,
          z_increment=(double)(starting_z-desired_z)/5;
          
  display.clearDisplay();
  Serial.println("Start");
  
  Berdiri();//x_val=y_val=8; z_val=3
  delay(2000);
  Serial.print("X increment");
  Serial.println(x_increment);
  Serial.print("z increment");
  Serial.println(z_increment);
  
  display.setCursor(0,0);
  display.print("X,Y inc = ");  
  display.setCursor(60,0);
  display.print(x_increment);
  display.setCursor(0,10);
  display.print("Z inc = ");
  display.setCursor(60,10);
  display.print(z_increment);

  display.display();
  button_state=digitalRead(button_pin1);

//without making sine-like movement value on z parameter
//while(1){
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      RightFront(i,8,desired_z);
//      LeftBack(i,8,desired_z);
//      delay(delay_servo); 
//    }
//    
//    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z; i=i+x_increment, j=j+z_increment){
//      RightFront(i,8,j);
//      LeftBack(i,8,j);
//      delay(delay_servo);
//    }
//
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      LeftFront(i,8,desired_z);
//      RightBack(i,8,desired_z);
//      delay(delay_servo);
//    }
//    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z;i=i+x_increment, j=j+z_increment){
//      LeftFront(i,8,j);
//      RightBack(i,8,j);
//      delay(delay_servo);
//    }
//  }
//<<<<<<< HEAD
  /*
   * //making z value on robot movement increase and decrease like sine signal
  while(1){
    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-x_increment, j=j-z_increment){
      RightFront(i,8,j);
      LeftBack(i,8,j);
      delay(delay_servo); 
    }
    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z; i=i+x_increment, j=j+z_increment){
      RightFront(i,8,j);
      LeftBack(i,8,j);
      delay(delay_servo);
    }
=======
}
>>>>>>> 0b2f46af5476f784212912c1c0d4665687caae0b

    for(double i=starting_x, j=starting_z; i>=desired_x, j>=desired_z; i=i-x_increment, j=j-z_increment){
      LeftFront(i,8,j);
      RightBack(i,8,j);
      delay(delay_servo);
    }
    for(double i=desired_x, j=desired_z;i<=starting_x, j<=starting_z;i=i+x_increment, j=j+z_increment){
      LeftFront(i,8,j);
      RightBack(i,8,j);
      delay(delay_servo);
    }
<<<<<<< HEAD
=======
    LeftFront(x,8,z);
    x0_=x;
    z0_=z;    
//    delay(00);
>>>>>>> 0b2f46af5476f784212912c1c0d4665687caae0b
  }
  */
//  //attempt to moving the legs simultanuously while the other is moving
//  //test result = success, but robot moving backward no matter what the order of sequence
//  while(1){
//    //setting up first move
//    for(double i=starting_x; i>=desired_x; i=i-x_increment){
//      RightFront(i,8,desired_z);
//      LeftBack(i,8,desired_z);
//      delay(delay_servo); 
//    }
//    while(1){
//      for(double  i=desired_x, j=desired_z, n=starting_x; 
//                  i<=starting_x, j<=starting_z, n>=desired_x;
//                  i=i+x_increment, j=j+z_increment, n=n-desired_x){
//        RightFront(i,8,j);
//        LeftBack(i,8,j);
//        LeftFront(n,8,desired_z);
//        RightBack(n,8,desired_z);
//        delay(delay_servo);
//      }
//      for(double  i=desired_x, j=desired_z, n=starting_x;
//                  i<=starting_x, j<=starting_z, n>=desired_x;
//                  i=i+x_increment, j=j+z_increment, n=n-desired_x){
//        LeftFront(i,8,j);
//        RightBack(i,8,j);
//        RightFront(n,8,desired_z);
//        LeftBack(n,8,desired_z);
//        delay(delay_servo);
//      }
//    }
//  }

  
//  attempt to moving the legs simultanuously while the other is moving
//  test result = success on moving forward, but unable to climb 1 cm obstacle
  while(button_state==LOW){
    button_state=digitalRead(button_pin1);
  }
  //setting up first move
  digitalWrite(LED_pin, HIGH);
  display.setCursor(0, 20);
  display.println("Starting");
//    display.startscrollright(0x00, 0x0F);
  for(double i=starting_y; i>=test_desired_y; i=i-x_increment){
    RightFront(8, i, desired_z);
    LeftBack(8,i, desired_z);
    delay(delay_servo); 
  }
  while(1){
    Serial.println("-----------------------------------------------");
    Serial.println("step RF and LB, ");
    for(double  i=test_desired_y, j=desired_z,      n=starting_y; 
                i<=starting_y,    j<=starting_z,    n>=test_desired_y;
                i=i+x_increment,  j=j+z_increment,  n=n-x_increment/*test_desired_y*/){
      RightFront(8,i,j);
      LeftBack(8,i,j);
      LeftFront(8,n,desired_z);
      RightBack(8,n,desired_z);
      delay(delay_servo);
      Serial.print("i="); Serial.println(i);
      Serial.print("j="); Serial.println(j);
      Serial.print("n="); Serial.println(n);
      Serial.println("-----------");
    }
    Serial.println("-----------------------------------------------");
    Serial.println("Step LF and RB");
    for(double  i=test_desired_y, j=desired_z, n=starting_y;
                i<=starting_x, j<=starting_z, n>=test_desired_y;
                i=i+x_increment, j=j+z_increment, n=n-x_increment/*test_desired_y*/){
      LeftFront(8,i,j);
      RightBack(8,i,j);
      RightFront(8,n,desired_z);
      LeftBack(8,n,desired_z);
      delay(delay_servo);
      Serial.print("i="); Serial.println(i);
      Serial.print("j="); Serial.println(j);
      Serial.print("n="); Serial.println(n);
      Serial.println("-----------");
    }
  }


/*
 * //testing step by step increment
  RightFront( 8, 8, 9);
  RightBack(  8, 8, 9);
  LeftFront(  8, 8, 9);
  LeftBack(   8, 8, 9);
  delay(1000);
  
  RightFront( 8, 7, 4);
  RightBack(  8, 8, 9);
  LeftFront(  8, 8, 9);
  LeftBack(   8, 7, 4);
  delay(1000);

  RightFront( 8, 6, 4);
  RightBack(  8, 8, 9);
  LeftFront(  8, 8, 9);
  LeftBack(   8, 6, 4);
  delay(1000);
  
  RightFront( 8, 5, 4);
  RightBack(  8, 8, 9);
  LeftFront(  8, 8, 9);
  LeftBack(   8, 5, 4);
  delay(1000);
  
  
  
  while(1){
    RightFront( 8, 5, 4);
    RightBack(  8, 8, 9);
    LeftFront(  8, 8, 9);
    LeftBack(   8, 5, 4);
    delay(1000);

    RightFront( 8, 6, 5);
    RightBack(  8, 7, 4);
    LeftFront(  8, 7, 4);
    LeftBack(   8, 6, 5);
    delay(1000);
    
    RightFront( 8, 7, 6);
    RightBack(  8, 6, 4);
    LeftFront(  8, 6, 4);
    LeftBack(   8, 7, 6);
    delay(1000);
    
    RightFront( 8, 8, 7);
    RightBack(  8, 5, 4);
    LeftFront(  8, 5, 4);
    LeftBack(   8, 8, 7);
    delay(1000);

    RightFront( 8, 8, 8);
    RightBack(  8, 5, 4);
    LeftFront(  8, 5, 4);
    LeftBack(   8, 8, 8);
    delay(1000);

    RightFront( 8, 8, 9);
    RightBack(  8, 5, 4);
    LeftFront(  8, 5, 4);
    LeftBack(   8, 8, 9);
    delay(1000);

/////////////////////////////////////////
    RightFront( 8, 8, 9);
    RightBack(  8, 5, 4);
    LeftFront(  8, 5, 4);
    LeftBack(   8, 8, 9);
    delay(1000);

    RightFront( 8, 7, 4);
    RightBack(  8, 6, 5);
    LeftFront(  8, 6, 5);
    LeftBack(   8, 7, 4);
    delay(1000);
    
    RightFront( 8, 6, 4);
    RightBack(  8, 7, 6);
    LeftFront(  8, 7, 6);
    LeftBack(   8, 6, 4);
    delay(1000);
    
    RightFront( 8, 5, 4);
    RightBack(  8, 8, 7);
    LeftFront(  8, 8, 7);
    LeftBack(   8, 5, 4);
    delay(1000);

    RightFront( 8, 5, 4);
    RightBack(  8, 8, 8);
    LeftFront(  8, 8, 8);
    LeftBack(   8, 5, 4);
    delay(1000);

    RightFront( 8, 5, 4);
    RightBack(  8, 8, 9);
    LeftFront(  8, 8, 9);
    LeftBack(   8, 5, 4);
    delay(1000);
  }
*/

  
//  while(1){
//    trajectoryPlanningMirrorB(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanningB(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanningMirror(6,20,2,3,3,4);
//    delay(10);
//    trajectoryPlanning(6,20,2,3,3,4);
//    delay(10);
//  }
}
