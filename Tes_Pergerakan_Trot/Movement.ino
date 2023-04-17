//testing standing position
void Berdiri(){
  double  x_standing=8,
          y_standing=8,
          z_standing=5;
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
