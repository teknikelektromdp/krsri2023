//testing standing position
void Berdiri(){
  LeftFront(10.5, 10.5, 3);
  LeftBack(10.5, 10.5, 3);
  RightFront(10.5, 10.5, 3);
  RightBack(10.5, 10.5, 3);
//  LeftFront(7, 7, 3);
//  LeftBack(7, 7, 3);
//  RightFront(7, 7, 3);
//  RightBack(7, 7, 3);
}

void Maju(){
  LeftFront(10.5, 10.5, 3);
    LeftBack(11.5, 9.5, 3);
    RightFront(11.5, 9.5, 3);
    RightBack(10.5, 10.5, 3);
    delay(100);
  while(1){
    //first step
    Serial.println("First step");
    //Raising right back up
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 3);
  //  RightFront(11.5, 9.5, 3);
    RightBack(11.5, 11.5, 1);
    delay(100);
    
    //moving right back forward
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 4);
  //  RightFront(11.5, 9.5, 4);
    RightBack(8, 12, 1);
    delay(100);

    //dropping right back down
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 4);
  //  RightFront(11.5, 9.5, 4);
    RightBack(6, 11, 3);
    delay(100);
 
     //raising right front up
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 4);
    RightFront(11.5, 10, 1);
  //  RightBack(9, 11, 3);
    delay(50);
    //moving right front forward
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 4);
    RightFront(9, 11, 1);
  //  RightBack(9, 11, 4);
    delay(50);
    //dropping right front down
  //  LeftFront(10.5, 10.5, 4);
  //  LeftBack(11.5, 9.5, 4);
    RightFront(9, 11, 3);
  //  RightBack(9, 11, 4);
  //  delay(10);
  
    
    delay(100);
    Serial.println("Second step");
    //moving right back, right front, and left front back
    RightFront(10.5, 10.5, 3);
    LeftFront(11.5, 8.5, 3);
  //  LeftBack(11.5, 9.5, 4);
    RightBack(11.5, 8.5, 3);
    delay(100);
  
  
    Serial.println("Third step");
    //Raising right back up
  //  RightFront(10.5, 10.5, 4);
    RightBack(11.5, 9.5, 3);
    LeftFront(11.5, 9.5, 3);
    LeftBack(11.5, 11.5, 1);
    delay(50);
    //moving right back forward
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(11.5, 9.5, 4);
  //  LeftFront(11.5, 9.5, 4);
    LeftBack(9, 11, 1);
    delay(50);
    //dropping right back down
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(11.5, 9.5, 4);
  //  LeftFront(11.5, 9.5, 4);
    LeftBack(9, 11, 3);
    delay(50);
    //raising right front up
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(11.5, 9.5, 4);
    LeftFront(11.5, 10, 1);
  //  LeftBack(9, 11, 3);
    delay(50);
    //moving right front forward
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(11.5, 9.5, 4);
    LeftFront(9, 11, 1);
  //  LeftBack(9, 11, 4);
    delay(50);
    //dropping right front down
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(11.5, 9.5, 4);
    LeftFront(9, 11, 3);
  //  LeftBack(9, 11, 4);
  //  delay(10);
  
    
    delay(100);
    Serial.println("Forth step");
    //moving right back, right front, and left front back
    LeftFront(10.5, 10.5, 3);
    RightFront(11.5, 8.5, 3);
  //  LeftBack(11.5, 9.5, 4);
    LeftBack(11.5, 8.5, 3);
    delay(50);
  //  delay(1000);
  //  Serial.println("lower left front leg");
  //  LeftFront(9.5, 11, 4);
  //  LeftBack(9.5, 11, 4);
  //  RightFront(10.5, 10.5, 4);
  //  RightBack(10.5, 10.5, 4);
    delay(100);
}
}
