void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  trajectoryPlanning(5,30,2,3,3,3);
  Serial.println("End of Motion 1");
  delay(3000);
  trajectoryPlanningMirror(5,30,2,3,3,3);
  Serial.println("End of Motion 2");
  delay(3000);

}

//function for converting degree value to radian
double Degree_to_Rad(double Degree)
{
  double rad = Degree*0.01745329252;
  return rad;
}

void trajectoryPlanning(int x0,float t,int deltaT,int AEPx,int fc,int z0)
{
  int step=t/deltaT;
  float x0_=x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step;i++)
  {
    if(i==0)
    {
      x=x0;
      z=z0;      
    }
    else
    {
      x=x0_+((x0+AEPx-x0_)/deltaT);
      z=fc*sin(Degree_to_Rad(180*((((i+1)*2)-t)/t)))+z0;
    }
    Serial.print("x");
    Serial.println(i);
    Serial.println(x);
    Serial.print("z: ");
    Serial.println(z);
    x0_=x;
    z0_=z;    
  }
}

void trajectoryPlanningMirror(int x0,float t,int deltaT,float AEPx,int fc,int z0)
{
  int step=t/deltaT;
  float x0_=AEPx+x0;
  float x=0;
  float z0_=z0;
  float z=0;
  for(int i=0;i<step;i++)
  {
    if(i==0)
    {
      x=AEPx+x0;
      z=z0;      
    }
    else
    {
      x=x0_+(((AEPx+x0)+(AEPx*-1)-x0_)/deltaT);    
      z=z0;
    }
    Serial.print("x");
    Serial.println(i);
    Serial.println(x);
    Serial.print("z: ");
    Serial.println(z);
    x0_=x;
    z0_=z;    
  }
}
