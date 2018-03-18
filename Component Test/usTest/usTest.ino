int trig1Pin = 2;
int echo1Pin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int us1Read = usRead(trig1Pin,echo1Pin);
  Serial.print("Distance 1 = ");
  Serial.print(us1Read);
  Serial.println(" cm");
  delay(100);
}

int usRead(int trigPin, int echoPin){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  return distance;
}

