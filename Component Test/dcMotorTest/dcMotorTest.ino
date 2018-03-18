int fwdRightPin = 6;
int bwdRightPin = 5;
int fwdLeftPin = 11;
int bwdLeftPin = 10;

void setup() {
  pinMode(fwdRightPin, OUTPUT);
  pinMode(bwdRightPin, OUTPUT);
  pinMode(fwdLeftPin, OUTPUT);
  pinMode(bwdLeftPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  /*
  digitalWrite(bwdPin,LOW);
  analogWrite(fwdPin, 150);
  delay(1000);
  digitalWrite(fwdPin,LOW);
  analogWrite(bwdPin,150);
  delay(1000);
  */
  digitalWrite(bwdRightPin,LOW);
  analogWrite(fwdRightPin, 150);
  
  digitalWrite(fwdLeftPin,LOW);
  analogWrite(bwdLeftPin, 150);
  
}
