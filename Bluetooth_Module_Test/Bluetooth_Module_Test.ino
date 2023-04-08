void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=0;
  for (i=0; i<=1000;i++){
    Serial.println(i);
    Serial1.println(i);
    delay(500);
  }
}
