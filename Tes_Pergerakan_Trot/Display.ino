void Display(double i, double j, double n){
  
  display.setCursor(0,0);   display.println("i =");
  display.setCursor(30,0);   display.println(i);
  display.setCursor(0,10);   display.println("j =");
  display.setCursor(30,10);   display.println(j);
  display.setCursor(0,20);   display.println("n =");
  display.setCursor(30,20);   display.println(n);
  display.display();
}
