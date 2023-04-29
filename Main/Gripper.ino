void gripMovement(String movement)
{
  //pixy.setServos(lifter, gripper)  limit (300-1000, 0-500)
  //lcg = lift and close gripper 
  if(movement == "lcg")
  {
    pixy.setServos(100, 0);
  }
  //lift and open gripper
  else if(movement == "log")
  {
    pixy.setServos(100, 500);
  }
  //put and open gripper
  else if(movement == "pog")
  {
    pixy.setServos(850, 500);
  }
  //put and close gripper
  else if(movement == "pcg"){
    pixy.setServos(850, 0);
  }
  else
  {
    pixy.setServos(950, 500);
  }
}

void initGripper()
{
  gripMovement("lcg");
  //turn on the led
  pixy.setLamp(0, 0);
}
