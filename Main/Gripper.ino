void gripMovement(String movement)
{
  //pixy.setServos(lifter, gripper)
  //lcg = lift and close gripper 
  if(movement == "lcg")
  {
    pixy.setServos(0, 25);
  }
  //lift and open gripper
  else if(movement == "log")
  {
    pixy.setServos(0, 500);
  }
  //put and open gripper
  else if(movement == "pog")
  {
    pixy.setServos(700, 500);
  }
  //put and close gripper
  else
  {
    pixy.setServos(600, 25);
  }
}

void initGripper()
{
  gripMovement("lcg");
  //turn on the led
  pixy.setLamp(0, 0);
}