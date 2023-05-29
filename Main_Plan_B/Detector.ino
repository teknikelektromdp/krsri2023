void initPixy()
{
  left_min = 40;
  left_max = 79;
//  right_min = 80;
//  right_max = 140;
  right_min = 120,
  right_max = 130;
  front_min = 60;
  front_max = 0;
  lock = 0;
  object1 = 0;
  pixy.init();
}

int getObjectLocation()
{
  //grab blocks!
  pixy.ccc.getBlocks(); 
  //if there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    if(pixy.ccc.blocks[0].m_x >= left_min && pixy.ccc.blocks[0].m_x <= left_max)
    {
      //To left side
      return -1;
    }
    else if(pixy.ccc.blocks[0].m_x >= right_min && pixy.ccc.blocks[0].m_x <= right_max)
    {
      return 1;
    }
    else
    {
      //To right side
      return -2;
    }
  } 
  //if there is no object detected
  else
  {
    return 0;
    // Serial.println("Not Detected");
  }
}

void detectObject(int object)
{
  if(object == 1)
  {
    while(object1==0)
    {
      int getObject = getObjectLocation();
      Serial.println(getObject);
      if(getObject==0)
      {
        for(int i=0; i<3; i++)
        {
          trotBasicLeftward(135,10);
//          enhancedTrotLeft(70); 
          delay(10);
        }
        delay(100);
        for(int i=0; i<3; i++)
        {
          trotBasicRightward(135,10);
//          enhancedTrotRight(70); 
          delay(10);
        }
      }
      else if(getObject==-1)
      {
        for(int i=0; i<3; i++)
        {
          trotBasicRightward(135,10);
//          enhancedTrotRight(70); 
          delay(10);
        }      
      }
      else if(getObject==-2)
      {
        for(int i=0; i<3; i++)
        {
          trotBasicLeftward(135, 10);
//          enhancedTrotLeft(70); 
          delay(10);
        } 
      }
      else if(getObject==1)
      {
        gripMovement("pog");
        lock = 1;
        while(lock == 1)
        {
          int distance = scan(GRIP);
          Serial.print("Distance :");
          Serial.println(distance);
//          while(distance > 15){
//            if(distance >100){
//              for(int i=0;i<2;i++){
//              enhancedTrotRight(70); 
//              delay(10);
//              }
//              for(int i=0;i<2;i++){
//                enhancedTrotLeft(70);
//                delay(10);
//              }
//            }
            back_distance = scan(BACK);
            left_distance = scan(LEFT_);
            right_distance = scan(RIGHT);
            front_distance = scan(FRONT);
            grip_distance  = scan(GRIP);
            bearing = getBearing();
            pitchRoll();
            display.clearDisplay();
            display.setCursor(0,0);
            display.print("grip=");  display.print(grip_distance);
            display.setCursor(10,0);
            display.print("roll=");  display.print(roll);
            display.setCursor(0,10);
            display.print("cmps=");  display.print(bearing);
            display.setCursor(0,20);
            display.print("b=");  display.print(back_distance);
            display.setCursor(10,20);
            display.print("r=");  display.print(right_distance);
            display.setCursor(0,30);
            display.print("f=");  display.print(front_distance);
            display.setCursor(10,30);
            display.print("l=");  display.print(left_distance);
            for(int i=0; i<(distance/5); i++){
              enhancedTrotBackward(100); 
//              trotBasicBackward(200,10); 
              Serial.print("i :");
              Serial.print(i);
              int _distance =scan(GRIP);
              Serial.print("\tgripper distance :");
              Serial.println(_distance);
              delay(10);
            }
            delay(1000);
            for(int i=0; i<4; i++){
              enhancedTrotRight(90); 
              delay(10);
            }
          lock = 0;
          object1 = 1;
        }
      }
    }
  }
  
  if(object == 2)
  {
//    gripMovement("sog");
    Gripper.write(90);
    pixy.setLamp(1,0);
    delay(100);
    int test_val = 600,
    right_min = 130,
    right_max = 140;
    int scan=0;
    object1=0;
    while(object1==0)
    {
      
      int getObject = getObjectLocation();
      Serial.println(getObject);
      Dynamixel.moveSpeed(7,test_val,150);
      if(getObject==1){
        pixy.setLamp(0,0);
        delay(500);
        pixy.setLamp(1,1);
        delay(500);
        
        object1=1;
      }
      test_val--;
      if(test_val == 400){
        test_val=600;
        scan=scan+1;
        if(scan%3==0){
          enhancedTrotHigherBackward(100,10);
        }
      }
      delay(10);
      
    }
    pixy.setLamp(0,0);
    delay(500);
//    Gripper.write(90);
  }
  if(object == 3)
  {
//    gripMovement("sog");
    Gripper.write(90);
    pixy.setLamp(1,0);
    delay(100);
    int test_val = 400,
    right_min = 130,
    right_max = 140;
    int scan=0;
    object1=0;
    while(object1==0)
    {
      
      int getObject = getObjectLocation();
      Serial.println(getObject);
      Dynamixel.moveSpeed(7,test_val,150);
      if(getObject==1){
        pixy.setLamp(0,0);
        delay(500);
        pixy.setLamp(1,1);
        delay(500);
        
        object1=1;
      }
      test_val++;
      if(test_val == 600){
        test_val=400;
        scan=scan+1;
        if(scan%3==0){
          enhancedTrotHigherBackward(100,10);
        }
      }
      delay(10);
      
    }
    pixy.setLamp(0,0);
    delay(500);
//    Gripper.write(90);
  }
}
