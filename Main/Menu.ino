void mainMenu()
{
  int menuState = digitalRead(menu_button);
  
  if (menuState == HIGH) {
    startPressed = millis();
    idleTime = startPressed - endPressed;
  } 
  else 
  {
    endPressed = millis();
    holdTime = endPressed - startPressed; 
  }

  if(holdTime >= 3000)
  {
    resetFunc();
  }
}

void showMenu() 
{
  cursor=0;
  display.clearDisplay();
  // show menu items:
  for (int i = 0; i<MENU_SIZE; i++) {
    display.drawString(2,i,menu[i]);
  }
  display.setCursor(0,0);
  display.print('>');
}

void displayMenu()
{
  while(start_==0)
  {
    //Stuck when reset button is released
    menuState = digitalRead(menu_button);
    startState = digitalRead(start_button);
    Serial.print(menuState);
    Serial.println(startState);
    if(startState == HIGH)
    {
      start_ = 1;
    }
    //filter out any noise by setting a time buffer
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if(menuState == HIGH)
      {
        menuCount=1;
        lastDebounceTime = millis(); //set the current time
      }  
    }
    if(menuCount==1)
    {
      if(start_count==0)
      {
        showMenu();
        start_count=start_count+1;
        menuCount=0;
      }
      else
      {
        display.setCursor(0,cursor);
        display.print(' ');
        cursor++;
        if (cursor>(MENU_SIZE-1)) cursor=0;
        // show cursor at new line:
        display.setCursor(0,cursor);
        display.print('>');
        menuCount=0;
      }
    }
  }
}
