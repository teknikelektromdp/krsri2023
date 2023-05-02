/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

void writeLog(String msg)
{
  // Length (with one extra character for the null terminator)
  int str_len = msg.length() + 1; 
  
  // Prepare the character array (the buffer) 
  char text[str_len];
  
  // Copy it over 
  msg.toCharArray(text, str_len);
  radio.write(&text, sizeof(text));
}

String intToString(int val)
{
  return String(val);
}


String longToString(int val)
{
  return String(val);
}

String floatToString(float val)
{
  char buf[6];
  dtostrf(val,5,2,buf);  

  return buf;
}

String doubleToString(double val)
{
  char buf[6];
  dtostrf(val,5,2,buf);  

  return buf;
}

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  writeLog(longToString(700));
  delay(1000);
}
