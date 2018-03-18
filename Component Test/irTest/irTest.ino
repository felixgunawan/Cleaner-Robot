int irLeftPin = A7;
int irRightPin = A6;


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int irLeftReading = analogRead(irLeftPin);
  Serial.print("Left : ");
  Serial.println(irLeftReading);
  int irRightReading = analogRead(irRightPin);
  Serial.print("Right : ");
  Serial.println(irRightReading);
  delay(500);
}
