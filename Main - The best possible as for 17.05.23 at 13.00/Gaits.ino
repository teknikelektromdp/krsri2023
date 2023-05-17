/* Initial Position */
void initialPosition(int speed)
{
  LeftFront(x_default, y_default, z_default, speed, 10);
  LeftBack(x_default, y_default, z_default, speed, 10);
  RightFront(x_default, y_default, z_default, speed, 10);
  RightBack(x_default, y_default, z_default, speed, 10);
}

/* Creep Algorithms */
void creepForward(int creepSpeed, double z_lift, int delay_servo)
{
  //First Cycle
  RightFront(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default+2;
  lastPositionRFY = y_default-2;
  lastPositionRFZ = z_default;
  LeftBack(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionLBX = x_default+2;
  lastPositionLBY = y_default-2;
  lastPositionLBZ = z_default;
  RightBack(x_default, y_default, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionRBX = x_default;
  lastPositionRBY = y_default;
  lastPositionRBZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  RightBack(lastPositionRBX-4, lastPositionRBY+3, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX-4;
  lastPositionRBY = lastPositionRBY+3;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
  // RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ, 40);
  // LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, 40);
  // LeftFront(x_default-2, y_default+2, z_default-1, 40);
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ-z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ-z_lift;
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX-3, lastPositionRFY+3, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX-3;
  lastPositionRFY = lastPositionRFY+3;
  delay(100/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);  
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(10);

  //Second Cycle
  RightBack(lastPositionRBX+4, lastPositionRBY-3, lastPositionRBZ, creepSpeed/2, delay_servo);
  //adjust this sequence
  delay(200);
  RightBack(lastPositionRBX+5, lastPositionRBY-5, lastPositionRBZ, creepSpeed/2, delay_servo);
  lastPositionRBX = lastPositionRBX+4;
  lastPositionRBY = lastPositionRBY-4;
  LeftFront(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionLFX = x_default+2;
  lastPositionLFY = y_default-2;
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ-z_lift;  
  delay(500/(creepSpeed/100));
  LeftBack(lastPositionLBX-6, lastPositionLBY+6, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX = lastPositionLBX-6;
  lastPositionLBY = lastPositionLBY+6;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);
  LeftFront(lastPositionLFX, lastPositionLFY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  LeftFront(lastPositionLFX-2, lastPositionLFY+2, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX-2;
  lastPositionLFY = lastPositionLFY+2;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX-2, lastPositionLFY+2, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
}

void creepBackward(int creepSpeed, double z_lift, int delay_servo)
{
  //First Cycle
  LeftBack(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionLBX = x_default-2;
  lastPositionLBY = y_default+2;
  lastPositionLBZ = z_default;
  RightFront(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default-2;
  lastPositionRFY = y_default+2;
  lastPositionRFZ = z_default;
  LeftFront(x_default, y_default, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLFX = x_default;
  lastPositionLFY = y_default;
  lastPositionLFZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  LeftFront(lastPositionLFX+4, lastPositionLFY-3, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX+4;
  lastPositionLFY = lastPositionLFY-3;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
  // RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ, 40);
  // LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, 40);
  // LeftFront(x_default-2, y_default+2, z_default-1, 40);
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ-z_lift;
  delay(500/(creepSpeed/100));
  LeftBack(lastPositionLBX+3, lastPositionLBY-3, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX = lastPositionLBX+3;
  lastPositionLBY = lastPositionLBY-3;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);  
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);

  //Second Cycle
  LeftFront(lastPositionLFX-4, lastPositionLFY+3, lastPositionLFZ, creepSpeed/2, delay_servo);
  //adjust this sequence
  delay(200);
  LeftFront(lastPositionLFX-5, lastPositionLFY+5, lastPositionLFZ, creepSpeed/2, delay_servo);
  lastPositionLFX = lastPositionLFX-4;
  lastPositionLFY = lastPositionLFY+4;
  RightBack(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionRBX = x_default-2;
  lastPositionRBY = y_default+2;
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ-z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ-z_lift;  
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX+4, lastPositionRFY-6, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX+4;
  lastPositionRFY = lastPositionRFY-6;
  delay(100/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(10);
  RightBack(lastPositionRBX, lastPositionRBY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  RightBack(lastPositionRBX+2, lastPositionRBY-2, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX+2;
  lastPositionRBY = lastPositionRBY-2;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX+2, lastPositionRBY-2, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
}

void creepRight(int creepSpeed, double z_lift, int delay_servo)
{
  //First Cycle
  LeftBack(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionLBX = x_default-2;
  lastPositionLBY = y_default+2;
  lastPositionLBZ = z_default;
  RightFront(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default-2;
  lastPositionRFY = y_default+2;
  lastPositionRFZ = z_default;
  LeftFront(x_default, y_default, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLFX = x_default;
  lastPositionLFY = y_default;
  lastPositionLFZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  LeftFront(lastPositionLFX-4, lastPositionLFY+3, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX-4;
  lastPositionLFY = lastPositionLFY+3;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
  // RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ, 40);
  // LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, 40);
  // LeftFront(x_default-2, y_default+2, z_default-1, 40);
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ-z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ-z_lift;
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX+3, lastPositionRFY-3, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX+3;
  lastPositionRFY = lastPositionRFY-3;
  delay(100/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);  
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(10);

  //Second Cycle
  LeftFront(lastPositionLFX+4, lastPositionLFY-3, lastPositionLFZ, creepSpeed/2, delay_servo);
  //adjust this sequence
  delay(200);
  LeftFront(lastPositionLFX+5, lastPositionLFY-5, lastPositionLFZ, creepSpeed/2, delay_servo);
  lastPositionLFX = lastPositionLFX+4;
  lastPositionLFY = lastPositionLFY-4;
  RightBack(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionRBX = x_default+2;
  lastPositionRBY = y_default-2;
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ-z_lift;  
  delay(500/(creepSpeed/100));
  LeftBack(lastPositionLBX+4, lastPositionLBY-4, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX = lastPositionLBX+4;
  lastPositionLBY = lastPositionLBY-4;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);
  RightBack(lastPositionRBX, lastPositionRBY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  RightBack(lastPositionRBX-2, lastPositionRBY+2, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX-2;
  lastPositionRBY = lastPositionRBY+2;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX-2, lastPositionRBY+2, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
}

void creepLeft(int creepSpeed, double z_lift, int delay_servo)
{
    //First Cycle
  RightFront(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default+2;
  lastPositionRFY = y_default-2;
  lastPositionRFZ = z_default;
  LeftBack(x_default+2, y_default-2, z_default, creepSpeed/2, delay_servo);
  lastPositionLBX = x_default+2;
  lastPositionLBY = y_default-2;
  lastPositionLBZ = z_default;
  RightBack(x_default, y_default, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionRBX = x_default;
  lastPositionRBY = y_default;
  lastPositionRBZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  RightBack(lastPositionRBX+4, lastPositionRBY-3, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX+4;
  lastPositionRBY = lastPositionRBY-3;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
  // RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ, 40);
  // LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, 40);
  // LeftFront(x_default-2, y_default+2, z_default-1, 40);
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ-z_lift;
  delay(500/(creepSpeed/100));
  LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX = lastPositionLBX+3;
  lastPositionLBY = lastPositionLBY-3;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);  
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);

  //Second Cycle
  RightBack(lastPositionRBX-4, lastPositionRBY+3, lastPositionRBZ, creepSpeed/2, delay_servo);
  //adjust this sequence
  delay(200);
  RightBack(lastPositionRBX-5, lastPositionRBY+5, lastPositionRBZ, creepSpeed/2, delay_servo);
  lastPositionRBX = lastPositionRBX-4;
  lastPositionRBY = lastPositionRBY+4;
  LeftFront(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionLFX = x_default-2;
  lastPositionLFY = y_default+2;
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ-z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ-z_lift;  
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX-4, lastPositionRFY+4, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX-4;
  lastPositionRFY = lastPositionRFY+4;
  delay(100/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(10);
  LeftFront(lastPositionLFX, lastPositionLFY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  LeftFront(lastPositionLFX+2, lastPositionLFY-2, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX+2;
  lastPositionLFY = lastPositionLFY-2;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX+2, lastPositionLFY-2, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
}

void creepSlightLeft(int creepSpeed, double z_lift, int delay_servo)
{
  RightBack(x_default-2, y_default+2, z_default, creepSpeed, delay_servo);
  lastPositionRBX = x_default-2;
  lastPositionRBY = y_default+2;
  lastPositionRBZ = z_default;
  LeftFront(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionLFX = x_default-2;
  lastPositionLFY = y_default+2;
  lastPositionLFZ = z_default;
  RightFront(x_default+2, y_default-2, z_default-z_lift, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default+2;
  lastPositionRFY = y_default-2;
  lastPositionRFZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX-4, lastPositionRFY+3, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX-4;
  lastPositionRFY = lastPositionRFY+3;
  delay(500/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX+3, lastPositionRBY-3, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX+3;
  lastPositionRBY = lastPositionRBY-3;
  LeftBack(x_default-2, y_default+2, z_default, creepSpeed, delay_servo);
  lastPositionLBX = x_default-2;
  lastPositionLBY = y_default+2;
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ-z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ-z_lift;
  delay(500/(creepSpeed/100));
  LeftFront(lastPositionLFX+2, lastPositionLFY-2, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX+2;
  lastPositionLFY = lastPositionLFY-2;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
  RightBack(lastPositionRBX+1, lastPositionRBY-1, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX+1;
  lastPositionRBY = lastPositionRBY-1;
  RightFront(lastPositionRFX+4, lastPositionRFY-3, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX+4;
  lastPositionRFY = lastPositionRFY-3;
  LeftBack(lastPositionLBX, lastPositionLBY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = z_default-z_lift;
  delay(500/(creepSpeed/100));
  LeftBack(lastPositionLBX+3, lastPositionLBY-3, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX =lastPositionLBX+3;
  lastPositionLBY = lastPositionLBY-3;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ-z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ-z_lift;
  delay(500/(creepSpeed/100));
  RightBack(lastPositionRBX-3, lastPositionRBY+3, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX-3;
  lastPositionRBY = lastPositionRBY+3;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
}

void creepSlightRight(int creepSpeed, double z_lift, int delay_servo)
{
  RightBack(x_default-2, y_default+2, z_default, creepSpeed, delay_servo);
  lastPositionRBX = x_default-2;
  lastPositionRBY = y_default+2;
  lastPositionRBZ = z_default;
  LeftFront(x_default-2, y_default+2, z_default, creepSpeed/2, delay_servo);
  lastPositionLFX = x_default-2;
  lastPositionLFY = y_default+2;
  lastPositionLFZ = z_default;
  RightFront(x_default, y_default, z_default-z_lift, creepSpeed/2, delay_servo);
  lastPositionRFX = x_default;
  lastPositionRFY = y_default;
  lastPositionRFZ = z_default-z_lift;
  delay(300/(creepSpeed/100));
  RightFront(lastPositionRFX+3, lastPositionRFY-2, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX+2;
  lastPositionRFY = lastPositionRFY-1;
  delay(300/(creepSpeed/100));
  RightFront(lastPositionRFX, lastPositionRFY, lastPositionRFZ+z_lift, creepSpeed, delay_servo);
  lastPositionRFZ = lastPositionRFZ+z_lift;
  delay(10);
  LeftFront(lastPositionLFX+2, lastPositionLFY-2, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX+2;
  lastPositionLFY = lastPositionLFY-2;
  LeftBack(x_default+2, y_default-2, z_default, creepSpeed, delay_servo);
  lastPositionLBX = x_default+2;
  lastPositionLBY = y_default-2;
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ-z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ-z_lift;
  delay(300/(creepSpeed/100));
  RightBack(lastPositionRBX+3, lastPositionRBY-3, lastPositionRBZ, creepSpeed, delay_servo);
  lastPositionRBX = lastPositionRBX+2;
  lastPositionRBY = lastPositionRBY-2;
  delay(100/(creepSpeed/100));
  RightBack(lastPositionRBX, lastPositionRBY, lastPositionRBZ+z_lift, creepSpeed, delay_servo);
  lastPositionRBZ = lastPositionRBZ+z_lift;
  delay(10);
  LeftFront(lastPositionLFX+4, lastPositionLFY-4, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX+4;
  lastPositionLFY = lastPositionLFY-4;
  RightFront(lastPositionRFX-3, lastPositionRFY+2, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX-2;
  lastPositionRFY = lastPositionRFY+1;
  LeftBack(lastPositionLBX, lastPositionLBY, z_default-z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = z_default-z_lift;
  delay(300/(creepSpeed/100));
  LeftBack(lastPositionLBX-3, lastPositionLBY+3, lastPositionLBZ, creepSpeed, delay_servo);
  lastPositionLBX = lastPositionLBX-2;
  lastPositionLBY = lastPositionLBY+2;
  delay(100/(creepSpeed/100));
  LeftBack(lastPositionLBX, lastPositionLBY, lastPositionLBZ+z_lift, creepSpeed, delay_servo);
  lastPositionLBZ = lastPositionLBZ+z_lift;
  delay(10);
  RightFront(lastPositionRFX-3, lastPositionRFY+2, lastPositionRFZ, creepSpeed, delay_servo);
  lastPositionRFX = lastPositionRFX-2;
  lastPositionRFY = lastPositionRFY+1;
  RightBack(lastPositionRBX-3, lastPositionRBY+3, lastPositionRBZ, creepSpeed, delay_servo);
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ-z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ-z_lift;
  delay(300/(creepSpeed/100));
  LeftFront(lastPositionLFX-3, lastPositionLFY+3, lastPositionLFZ, creepSpeed, delay_servo);
  lastPositionLFX = lastPositionLFX-2;
  lastPositionLFY = lastPositionLFY+2;
  delay(100/(creepSpeed/100));
  LeftFront(lastPositionLFX, lastPositionLFY, lastPositionLFZ+z_lift, creepSpeed, delay_servo);
  lastPositionLFZ = lastPositionLFZ+z_lift;
  delay(10);
}

/* Trot Algorithms */
void trotBasicForward(int speed, int delay_servo)
{
  // LeftFront(7,7,3,speed,delay_servo);
  // RightBack(7,7,3,speed,delay_servo);
  // delay(1);
  RightFront(7,5,2.5,speed,delay_servo);
  LeftBack(7,5,2.5,speed,delay_servo);
  LeftFront(5,7,0.5,speed,delay_servo);
  RightBack(5,7,0.5,speed,delay_servo);
  delay(1);
  // LeftFront(4,7,2,speed,delay_servo);
  // RightBack(4,7,2,speed,delay_servo);
  // delay(1);
  // RightFront(7,4,2,speed,delay_servo);
  // LeftBack(7,4,2,speed,delay_servo);
  // delay(1);
  LeftFront(7,5,2.5,speed,delay_servo);
  RightBack(7,5,2.5,speed,delay_servo);
  RightFront(5,7,0.5,speed,delay_servo);
  LeftBack(5,7,0.5,speed,delay_servo);
  // delay(1);
  // RightFront(4,7,2,speed,delay_servo);
  // LeftBack(4,7,2,speed,delay_servo);
  delay(1);
}

void trotBasicBackward(int speed, int delay_servo)
{
  // LeftFront(7,7,3,speed,delay_servo);
  // RightBack(7,7,3,speed,delay_servo);
  // delay(1);
  RightFront(5,7,2.5,speed,delay_servo);
  LeftBack(5,7,2.5,speed,delay_servo);
  LeftFront(7,5,0.5,speed,delay_servo);
  RightBack(7,5,0.5,speed,delay_servo);
  delay(1);
  // LeftFront(4,7,2,speed,delay_servo);
  // RightBack(4,7,2,speed,delay_servo);
  // delay(1);
  // RightFront(7,4,2,speed,delay_servo);
  // LeftBack(7,4,2,speed,delay_servo);
  // delay(1);
  LeftFront(5,7,2.5,speed,delay_servo);
  RightBack(5,7,2.5,speed,delay_servo);
  RightFront(7,5,0.5,speed,delay_servo);
  LeftBack(7,5,0.5,speed,delay_servo);
  // delay(1);
  // RightFront(4,7,2,speed,delay_servo);
  // LeftBack(4,7,2,speed,delay_servo);
  delay(1);
}


void trotBasicLeftward(int speed, int delay_servo)
{
    LeftFront(5,8,2.5,speed,delay_servo);
    RightBack(5,7.5,2.5,speed,delay_servo);
    RightFront(5,7.5,0.5,speed,delay_servo);
    LeftBack(5,7.5,0.5,speed,delay_servo);
    delay(1);
    RightFront(7.5,5,2.5,speed,delay_servo);
    LeftBack(7.5,5,2.5,speed,delay_servo);
    LeftFront(8,5,0.5,speed,delay_servo);
    RightBack(7.5,5,0.5,speed,delay_servo);
    delay(1);

//  for(double x=8, z=2.5; x>=5, z>=0.5; x--, z--){
//    LeftFront(x,8,2.5,400,delay_servo);
//    RightBack(x,7.5,2.5,400,delay_servo);
//    RightFront(x,7.5,0.5,400,delay_servo);
//    LeftBack(x,7.5,0.5,400,delay_servo);
//    delay(1);
//    RightFront(7.5,5,2.5,speed,delay_servo);
//    LeftBack(7.5,5,2.5,speed,delay_servo);
//    LeftFront(8,5,0.5,speed,delay_servo);
//    RightBack(7.5,5,0.5,speed,delay_servo);
//    delay(1);
//  }
}

void trotBasicRightward(int speed, int delay_servo)
{
//  LeftFront(7,5,2.5,speed,delay_servo);
//  RightBack(7,5,2.5,speed,delay_servo);
//  RightFront(7,5,0.5,speed,delay_servo);
//  LeftBack(7,5,0.5,speed,delay_servo);
//  delay(1);
//  RightFront(5,7,2.5,speed,delay_servo);
//  LeftBack(5,7,2.5,speed,delay_servo);
//  LeftFront(5,7,0.5,speed,delay_servo);
//  RightBack(5,7,0.5,speed,delay_servo);
//  delay(1);
//  
  LeftFront(8,5,2.5,speed,delay_servo);
  RightBack(7.5,5,2.5,speed,delay_servo);
  RightFront(7.5,5,0.5,speed,delay_servo);
  LeftBack(7.5,5,0.5,speed,delay_servo);
  delay(1);
  RightFront(5,7.5,2.5,speed,delay_servo);
  LeftBack(5,7.5,2.5,speed,delay_servo);
  LeftFront(5,8,0.5,speed,delay_servo);
  RightBack(5,7.5,0.5,speed,delay_servo);
  delay(1);
}

void trotBasicSlightRight(int speed)
{
  RightFront(8,5,3.5,speed,10);
  LeftBack(5,8,3.5,speed,10);
  delay(30);
  RightFront(8,8,5,speed,10);
  LeftBack(8,8,5,speed,10);
  delay(30);
  LeftFront(5,8,3.5,speed,10);
  RightBack(8,5,3.5,speed,10);
  delay(30);
  LeftFront(8,8,5,speed,10);
  RightBack(8,8,5,speed,10);
  delay(30);
}

void trotBasicSlightLeft(int speed)
{
  RightFront(5,8,3.5,speed,10);
  LeftBack(8,5,3.5,speed,10);
  delay(30);
  RightFront(8,8,5,speed,10);
  LeftBack(8,8,5,speed,10);
  delay(30);
  LeftFront(8,5,3.5,speed,10);
  RightBack(5,8,3.5,speed,10);
  delay(30);
  LeftFront(8,8,5,speed,10);
  RightBack(8,8,5,speed,10);
  delay(30);
}

void enhancedTrotForward(int speed)
{
  LeftFront(8,8,4,speed,2);
  RightBack(8,8,4,speed,2);
  delay(1);
  RightFront(8,5,3,speed,2);
  LeftBack(8,5,3,speed,2);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  delay(1);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  delay(1);
  RightFront(8,5,2.5,speed,2);
  LeftBack(8,5,2,speed,2);
  delay(1);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  RightFront(5,8,2.5,speed,2);
  LeftBack(5,8,2,speed,2);
  delay(1);
  RightFront(5,8,3,speed,2);
  LeftBack(5,8,3,speed,2);
  delay(1);
}

void enhancedTrotBackward(int speed)
{
  LeftFront(8,8,4,speed,2);
  RightBack(8,8,4,speed,2);
  delay(1);
  RightFront(5,8,3,speed,2);
  LeftBack(5,8,3,speed,2);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  delay(1);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  delay(1);
  RightFront(5,8,2.5,speed,2);
  LeftBack(5,8,2,speed,2);
  delay(1);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  RightFront(8,5,2.5,speed,2);
  LeftBack(8,5,2,speed,2);
  delay(1);
  RightFront(8,5,3,speed,2);
  LeftBack(8,5,3,speed,2);
  delay(1);
}

void enhancedTrotBackwardv2(int speed, float inc){
  LeftFront(8,8,4+inc,speed,2);
  RightBack(8,8,4+inc,speed,2);
  delay(1);
  RightFront(5,8,3+inc,speed,2);
  LeftBack(5,8,3+inc,speed,2);
  LeftFront(8,5,3+inc,speed,2);
  RightBack(8,5,3+inc,speed,2);
  delay(1);
  LeftFront(8,5,3+(inc/3),speed,2);
  RightBack(8,5,3+(inc/3),speed,2);
  delay(1);
  RightFront(5,8,2.5+(inc/3),speed,2);
  LeftBack(5,8,2+(inc/3),speed,2);
  delay(1);
  LeftFront(5,8,3+inc,speed,2);
  RightBack(5,8,3+inc,speed,2);
  RightFront(8,5,2.5+(inc/3),speed,2);
  LeftBack(8,5,2+(inc/3),speed,2);
  delay(1);
  RightFront(8,5,3+inc,speed,2);
  LeftBack(8,5,3+inc,speed,2);
  delay(1);
}

void enhancedTrotLeft(int speed)
{
  LeftFront(8,8,4,speed,2);
  RightBack(8,8,4,speed,2);
  delay(1);
  RightFront(8,5,3,speed,2);
  LeftBack(8,5,3,speed,2);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  delay(1);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  delay(1);
  RightFront(5,8,2.5,speed,2);
  LeftBack(5,8,2,speed,2);
  delay(1);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  RightFront(5,8,2.5,speed,2);
  LeftBack(5,8,2,speed,2);
  delay(1);
  RightFront(5,8,3,speed,2);
  LeftBack(5,8,3,speed,2);
  delay(1);
}

void enhancedTrotRight(int speed)
{
  LeftFront(8,8,4,speed,2);
  RightBack(8,8,4,speed,2);
  delay(1);
  RightFront(5,8,3,speed,2);
  LeftBack(5,8,3,speed,2);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  delay(1);
  LeftFront(5,8,3,speed,2);
  RightBack(5,8,3,speed,2);
  delay(1);
  RightFront(8,5,2.5,speed,2);
  LeftBack(8,5,2,speed,2);
  delay(1);
  LeftFront(8,5,3,speed,2);
  RightBack(8,5,3,speed,2);
  RightFront(8,5,2.5,speed,2);
  LeftBack(8,5,2,speed,2);
  delay(1);
  RightFront(5,8,3,speed,2);
  LeftBack(5,8,3,speed,2);
  delay(1);
}

/* Please dont remove */
//void enhancedTrotHigherForward(int speed, int delay_servo)
//{
//  LeftFront(8,8,3,speed,delay_servo);
//  RightBack(8,8,3,speed,delay_servo);
//  delay(10);
//  RightFront(8,5,3,speed,delay_servo);
//  LeftBack(8,5,3,speed,delay_servo);
//  LeftFront(5,8,2,speed,delay_servo);
//  RightBack(5,8,1,speed,delay_servo);
//  delay(10);
//  LeftFront(5,8,3,speed,delay_servo);
//  RightBack(5,8,3,speed,delay_servo);
//  delay(10);
//  RightFront(8,5,1.5,speed,delay_servo);
//  LeftBack(8,5,0.5,speed,delay_servo);
//  delay(10);
//  LeftFront(8,5,3,speed,delay_servo);
//  RightBack(8,5,3,speed,delay_servo);
//  RightFront(5,8,2,speed,delay_servo);
//  LeftBack(5,8,1,speed,delay_servo);
//  delay(10);
//  RightFront(5,8,3,speed,delay_servo);
//  LeftBack(5,8,3,speed,delay_servo);
//  delay(10);
//}

void enhancedTrotHigherForward(int speed, int delay_servo)
{
  LeftFront(8,8,3,speed,delay_servo);
  RightBack(8,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,5,3,speed,delay_servo);
  LeftBack(8,5,3,speed,delay_servo);
  LeftFront(5,8,2,speed,delay_servo);
  RightBack(5,8,0.4,speed,delay_servo);
  delay(10);
  LeftFront(5,8,3,speed,delay_servo);
  RightBack(5,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,5,2,speed,delay_servo);
  LeftBack(8,5,0.4,speed,delay_servo);
  delay(10);
  LeftFront(8,5,3,speed,delay_servo);
  RightBack(8,5,3,speed,delay_servo);
  RightFront(5,8,2,speed,delay_servo);
  LeftBack(5,8,0.4,speed,delay_servo);
  delay(10);
  RightFront(5,8,3,speed,delay_servo);
  LeftBack(5,8,3,speed,delay_servo);
  delay(10);
}
void enhancedTrotHigherBackward(int speed, int delay_servo)
{
  LeftFront(8,8,3,speed,delay_servo);
  RightBack(8,8,3,speed,delay_servo);
  delay(10);
  RightFront(5,8,3,speed,delay_servo);
  LeftBack(5,8,3,speed,delay_servo);
  LeftFront(8,5,2,speed,delay_servo);
  RightBack(8,5,0.4,speed,delay_servo);
  delay(10);
  LeftFront(8,5,3,speed,delay_servo);
  RightBack(8,5,3,speed,delay_servo);
  delay(10);
  RightFront(5,8,2,speed,delay_servo);
  LeftBack(5,8,0.4,speed,delay_servo);
  delay(10);
  LeftFront(5,8,3,speed,delay_servo);
  RightBack(5,8,3,speed,delay_servo);
  RightFront(8,5,2,speed,delay_servo);
  LeftBack(8,5,0.4,speed,delay_servo);
  delay(10);
  RightFront(8,5,3,speed,delay_servo);
  LeftBack(8,5,3,speed,delay_servo);
  delay(10);
}
void enhancedTrotHigherRight(int speed, int delay_servo)
{
  LeftFront(8,8,3,speed,delay_servo);
  RightBack(8,8,3,speed,delay_servo);
  delay(10);
  RightFront(5,8,3,speed,delay_servo);
  LeftBack(5,8,3,speed,delay_servo);
  LeftFront(5,8,2,speed,delay_servo);
  RightBack(5,8,0.4,speed,delay_servo);
  delay(10);
  LeftFront(5,8,3,speed,delay_servo);
  RightBack(5,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,5,2,speed,delay_servo);
  LeftBack(8,5,0.4,speed,delay_servo);
  delay(10);
  LeftFront(8,5,3,speed,delay_servo);
  RightBack(8,5,3,speed,delay_servo);
  RightFront(8,5,2,speed,delay_servo);
  LeftBack(8,5,0.4,speed,delay_servo);
  delay(10);
  RightFront(5,8,3,speed,delay_servo);
  LeftBack(5,8,3,speed,delay_servo);
  delay(10);
}

void enhancedTrotHigherLeft(int speed, int delay_servo)
{
  LeftFront(8,8,3,speed,delay_servo);
  RightBack(8,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,5,3,speed,delay_servo);
  LeftBack(8,5,3,speed,delay_servo);
  LeftFront(8,5,2,speed,delay_servo);
  RightBack(8,5,0.4,speed,delay_servo);
  delay(10);
  LeftFront(8,5,3,speed,delay_servo);
  RightBack(8,5,3,speed,delay_servo);
  delay(10);
  RightFront(5,8,2,speed,delay_servo);
  LeftBack(5,8,0.4,speed,delay_servo);
  delay(10);
  LeftFront(5,8,3,speed,delay_servo);
  RightBack(5,8,3,speed,delay_servo);
  RightFront(5,8,2,speed,delay_servo);
  LeftBack(5,8,0.4,speed,delay_servo);
  delay(10);
  RightFront(5,8,3,speed,delay_servo);
  LeftBack(5,8,3,speed,delay_servo);
  delay(10);
}

void enhancedTrotHigherLeftTurn(int speed, int delay_servo)
{
  LeftFront(8,4,3,speed,delay_servo);
  RightBack(4,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,4,3,speed,delay_servo);
  LeftBack(4,8,3,speed,delay_servo);
  LeftFront(8,4,1.5,speed,delay_servo);
  RightBack(4,8,1.5,speed,delay_servo);
  delay(10);
  LeftFront(8,4,3,speed,delay_servo);
  RightBack(4,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,4,1.5,speed,delay_servo);
  LeftBack(4,8,1.5,speed,delay_servo);
  delay(10);
  LeftFront(8,4,3,speed,delay_servo);
  RightBack(4,8,3,speed,delay_servo);
  RightFront(4,8,1.5,speed,delay_servo);
  LeftBack(8,4,1.5,speed,delay_servo);
  delay(10);
  RightFront(4,8,3,speed,delay_servo);
  LeftBack(8,4,3,speed,delay_servo);
  delay(10);
}

void enhancedTrotLowerLeftTurn(int speed, int delay_servo)
{
  LeftFront(8,6,3,speed,delay_servo);
  RightBack(6,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,6,3,speed,delay_servo);
  LeftBack(6,8,3,speed,delay_servo);
  LeftFront(8,6,1.5,speed,delay_servo);
  RightBack(6,8,1.5,speed,delay_servo);
  delay(10);
  LeftFront(8,6,3,speed,delay_servo);
  RightBack(6,8,3,speed,delay_servo);
  delay(10);
  RightFront(8,6,1.5,speed,delay_servo);
  LeftBack(6,8,1.5,speed,delay_servo);
  delay(10);
  LeftFront(8,6,3,speed,delay_servo);
  RightBack(6,8,3,speed,delay_servo);
  RightFront(6,8,1.5,speed,delay_servo);
  LeftBack(8,6,1.5,speed,delay_servo);
  delay(10);
  RightFront(6,8,3,speed,delay_servo);
  LeftBack(8,6,3,speed,delay_servo);
  delay(10);
}

void enhancedTrotHigherRightTurn(int speed, int delay_servo)
{
  LeftFront(4,8,3,speed,delay_servo);
  RightBack(8,4,3,speed,delay_servo);
  delay(10);
  RightFront(4,8,3,speed,delay_servo);
  LeftBack(8,4,3,speed,delay_servo);
  LeftFront(4,8,1.5,speed,delay_servo);
  RightBack(8,4,1.5,speed,delay_servo);
  delay(10);
  LeftFront(4,8,3,speed,delay_servo);
  RightBack(8,4,3,speed,delay_servo);
  delay(10);
  RightFront(4,8,1.5,speed,delay_servo);
  LeftBack(8,4,1.5,speed,delay_servo);
  delay(10);
  LeftFront(4,8,3,speed,delay_servo);
  RightBack(8,4,3,speed,delay_servo);
  RightFront(8,4,1.5,speed,delay_servo);
  LeftBack(4,8,1.5,speed,delay_servo);
  delay(10);
  RightFront(8,4,3,speed,delay_servo);
  LeftBack(4,8,3,speed,delay_servo);
  delay(10);
}

void enhancedTrotLowerRightTurn(int speed, int delay_servo)
{
  LeftFront(6,8,3,speed,delay_servo);
  RightBack(8,6,3,speed,delay_servo);
  delay(10);
  RightFront(6,8,3,speed,delay_servo);
  LeftBack(8,6,3,speed,delay_servo);
  LeftFront(6,8,1.5,speed,delay_servo);
  RightBack(8,6,1.5,speed,delay_servo);
  delay(10);
  LeftFront(6,8,3,speed,delay_servo);
  RightBack(8,6,3,speed,delay_servo);
  delay(10);
  RightFront(6,8,1.5,speed,delay_servo);
  LeftBack(8,6,1.5,speed,delay_servo);
  delay(10);
  LeftFront(6,8,3,speed,delay_servo);
  RightBack(8,6,3,speed,delay_servo);
  RightFront(8,6,1.5,speed,delay_servo);
  LeftBack(6,8,1.5,speed,delay_servo);
  delay(10);
  RightFront(8,6,3,speed,delay_servo);
  LeftBack(6,8,3,speed,delay_servo);
  delay(10);
}

void trot90DegreeRightTurn(int repeat){
  for(int i=0; i<5*repeat; i++){
    enhancedTrotHigherRightTurn(500,10);
  }
}
void trot90DegreeLeftTurn(int repeat){
  for(int i=0; i<5*repeat; i++){
    enhancedTrotHigherLeftTurn(500,10);
  }
}

/*  still need improvement  */
void fastMove(int fast_speed){
  int startingx=8,  startingz=5,
      desiredx=5,   desiredz=2,
      delayservo=1;
  double  x_increment=(double)(startingx-desiredx)/5,
          z_increment=(double)(startingz-desiredz)/5;
  for(double i=startingx;i>=desiredx; i=i-x_increment){
    RightFront(8, i, desiredz,400,1);
    LeftBack(8, i, desiredz,400,1);
    delay(delayservo);
    writeLog("x=8");
    writeLog("y=");
    writeLog(doubleToString(i));
    writeLog("desiredz =");
    writeLog(doubleToString(desiredz));
  }
  delay(10);
  writeLog("Start moving");
  while(true){
    for(double i=desiredx, j=desiredz, n=startingx;  i<=startingx, j<=startingz, n>=desiredx; i=i+x_increment, j=j+z_increment, n=n-desiredx){
      RightFront(8,i,j, fast_speed, delayservo);
      LeftBack(8,i,j, fast_speed, delayservo);
      LeftFront(8,n,desiredz, fast_speed, delayservo);
      RightBack(8,n,desiredz, fast_speed, delayservo);
      delay(delayservo);
      writeLog("i=");
      writeLog(doubleToString(i));
      writeLog("n=");
      writeLog(doubleToString(n));
      writeLog("j=");
      writeLog(doubleToString(j));
      writeLog("desired z=");
      writeLog(doubleToString(desiredz));
    }
    writeLog("--------------------------------------------------------");
    for(double i=desiredx, j=desiredz, n=startingx;  i<=startingx, j<=startingz, n>=desiredx; i=i+x_increment, j=j+z_increment, n=n-desiredx){
      LeftFront(8,i,j, fast_speed, delayservo);
      RightBack(8,i,j, fast_speed, delayservo);
      RightFront(8,n,desiredz, fast_speed, delayservo);
      LeftBack(8,n,desiredz, fast_speed, delayservo);
      delay(delayservo);
      writeLog("i=");
      writeLog(doubleToString(i));
      writeLog("n=");
      writeLog(doubleToString(n));
      writeLog("j=");
      writeLog(doubleToString(j));
      writeLog("desired z=");
      writeLog(doubleToString(desiredz));
    }
    writeLog("--------------------------------------------------------");
  }
}
