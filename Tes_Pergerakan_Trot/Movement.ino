//testing standing position
void Berdiri(){
  double  x_standing=7,//(8),
          y_standing=7,//(8)
          z_standing=4;//5
//  LeftFront(10.5, 10.5, 3);
//  LeftBack(10.5, 10.5, 3);
//  RightFront(10.5, 10.5, 3);
//  RightBack(10.5, 10.5, 3);
  LeftFront(x_standing, y_standing, z_standing);
  LeftBack(x_standing, y_standing, z_standing);
  RightFront(x_standing, y_standing, z_standing);
  RightBack(x_standing, y_standing, z_standing);
}

void trajectoryPlanning(int x0,float t,int deltaT,int AEPx,int fc,int z0){
  int step_=t/deltaT;
  float x0_=x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++){
    if(i==0){
      x=x0;
      z=z0;      
    }
    else{
      x=x0_+((x0+AEPx-x0_)/deltaT);
      z=z0;
    }
    LeftFront(x,8,z);
    RightBack(x,8,z);
    x0_=x;
    z0_=z;
  }
}

void trajectoryPlanningMirror(int x0,float t,int deltaT,float AEPx,int fc,int z0){
  int step_=t/deltaT;
  float x0_=AEPx+x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++){
    if(i==0){
      x=AEPx+x0;
      z=z0;      
    }
    else{
      x=x0_+(((AEPx+x0)+(AEPx*-1)-x0_)/deltaT);    
      z=fc*sin(Degree_to_Rad(180*((((i+1)*2)-t)/t)))+z0;
    }
    LeftFront(x,8,z);
    RightBack(x,8,z);
    x0_=x;
    z0_=z;    
  }
}

void trajectoryPlanningB(int x0,float t,int deltaT,int AEPx,int fc,int z0){
  int step_=t/deltaT;
  float x0_=x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++){
    if(i==0){
      x=x0;
      z=z0;      
    }
    else{
      x=x0_+((x0+AEPx-x0_)/deltaT);
      z=z0;
    }
    RightFront(x,8,z);
    LeftBack(x,8,z);
    x0_=x;
    z0_=z;    
  }
}

void trajectoryPlanningMirrorB(int x0,float t,int deltaT,float AEPx,int fc,int z0){
  int step_=t/deltaT;
  float x0_=AEPx+x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step_;i++){
    if(i==0){
      x=AEPx+x0;
      z=z0;      
    }
    else{
      x=x0_+(((AEPx+x0)+(AEPx*-1)-x0_)/deltaT);    
      z=fc*sin(Degree_to_Rad(180*((((i+1)*2)-t)/t)))+z0;
    }
    RightFront(x,8,z);
    LeftBack(x,8,z);
    x0_=x;
    z0_=z;    
  }
}
void ForwardMovement(double starting_x, double desired_x, double starting_z, double desired_z, double x_increment, double z_increment, double delay_servo){
  //setting up first move
  for(double i=starting_x; i>=desired_x; i=i-x_increment){
    RightFront(i,8,desired_z);
    LeftBack(i,8,desired_z);
    delay(delay_servo); 
  }
  while(1){
    for(double  i=desired_x,      j=desired_z,      n=starting_x; 
                i<=starting_x,    j<=starting_z,    n>=desired_x;
                i=i+x_increment,  j=j+z_increment,  n=n-x_increment){
      RightFront(i,8,j);
      LeftBack(i,8,j);
      LeftFront(n,8,desired_z);
      RightBack(n,8,desired_z);
      
      display.clearDisplay();
      Display(i, j, n);

      //reset condition
      if(digitalRead(button_pin2)==HIGH){
        digitalWrite(LED_pin, LOW);
        button_state=digitalRead(button_pin1);
        resetFunc();  
      }
      delay(delay_servo);
    }
    for(double  i=desired_x, j=desired_z, n=starting_x;
                i<=starting_x, j<=starting_z, n>=desired_x;
                i=i+x_increment, j=j+z_increment, n=n-x_increment){
      LeftFront(i,8,j);
      RightBack(i,8,j);
      RightFront(n,8,desired_z);
      LeftBack(n,8,desired_z);
      
      display.clearDisplay();
      Display(i, j, n);

      //reset condition
      if(digitalRead(button_pin2)==HIGH){
        digitalWrite(LED_pin, LOW);
        button_state=digitalRead(button_pin1);
        resetFunc();  
      }
      delay(delay_servo);
    }
  }
}

void BackwardMovement(double starting_y, double desired_y, double starting_z, double desired_z, double y_increment, double z_increment, double delay_servo){
  for(double i=starting_y; i>=desired_y; i=i-y_increment){
    RightFront(8, i, desired_z);
    LeftBack(8,i, desired_z);
    delay(delay_servo); 
  }
  while(1){
    for(double  i=desired_y,      j=desired_z,      n=starting_y; 
                i<=starting_y,    j<=starting_z,    n>=desired_y;
                i=i+y_increment,  j=j+z_increment,  n=n-y_increment){
      RightFront(8,i,j);
      LeftBack(8,i,j);
      LeftFront(8,n,desired_z);
      RightBack(8,n,desired_z);
      display.clearDisplay();
      Display(i, j, n);

      //reset condition
      if(digitalRead(button_pin2)==HIGH){
        digitalWrite(LED_pin, LOW);
        button_state=digitalRead(button_pin1);
        resetFunc();  
      }
      delay(delay_servo);
    }

    for(double  i=desired_y,      j=desired_z,      n=starting_y;
                i<=starting_y,    j<=starting_z,    n>=desired_y;
                i=i+y_increment,  j=j+z_increment,  n=n-y_increment){
      LeftFront(8,i,j);
      RightBack(8,i,j);
      RightFront(8,n,desired_z);
      LeftBack(8,n,desired_z);
      display.clearDisplay();
      Display(i, j, n);

      //reset condition
      if(digitalRead(button_pin2)==HIGH){
        digitalWrite(LED_pin, LOW);
        button_state=digitalRead(button_pin1);
        resetFunc();  
      }
      delay(delay_servo);
    }
  }
}
