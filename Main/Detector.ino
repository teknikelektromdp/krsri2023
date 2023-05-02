void initPixy()
{
  left_min = 40;
  left_max = 79;
  right_min = 80;
  right_max = 140;
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
          trotBasicLeftward(100,10);
//          enhancedTrotLeft(70); 
          delay(10);
        }
        delay(100);
        for(int i=0; i<5; i++)
        {
          trotBasicRightward(100,10);
//          enhancedTrotRight(70); 
          delay(10);
        }
      }
      else if(getObject==-1)
      {
        for(int i=0; i<3; i++)
        {
          trotBasicRightward(100,10);
//          enhancedTrotRight(70); 
          delay(10);
        }      
      }
      else if(getObject==-2)
      {
        for(int i=0; i<3; i++)
        {
          trotBasicLeftward(100, 10);
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
            for(int i=0; i<(distance/5); i++){
              enhancedTrotBackward(100); 
              Serial.print("i :");
              Serial.print(i);
              int _distance =scan(GRIP);
              Serial.print("\tgripper distance :");
              Serial.println(_distance);
              delay(10);
            }
            delay(1000);
            for(int i=0; i<4; i++){
              enhancedTrotRight(70); 
              delay(10);
            }
//          }
          
          // delay(1000);
          // for(int i=0; i<1; i++)
          // {
          //   enhancedTrotBackward(70); 
          //   delay(10);
          // } 
          // delay(2000); 
          // gripMovement("pcg");
          lock = 0;
          object1 = 1;
        }
      }
    }
  }
}
