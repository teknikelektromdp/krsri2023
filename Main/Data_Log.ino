void initLogger()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();  
}

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
