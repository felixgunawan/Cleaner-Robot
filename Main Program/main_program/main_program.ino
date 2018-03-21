#include <SoftwareSerial.h>

#define MAX_SPEED 200
#define MIN_SPEED 50
#define INC_SPEED 20
//Bluetooth
SoftwareSerial BT(8, 9); 
//DC Motor
int fwdRightPin = 6;
int bwdRightPin = 5;
int fwdLeftPin = 11;
int bwdLeftPin = 10;
//US Front
int trig1Pin = 2;
int echo1Pin = 3;
//IR Left&Right
int irLeftPin = A7;
int irRightPin = A6;
//Obstacle
int leftObstacle;
int rightObstacle;
int frontObstacle;

long randNumber;
char cmd;
int speedRight = 0;
int speedLeft = 0;
int mode = 0;//0 : random, 1 : remote

void setup() {
  BT.begin(9600);
  BT.println("Hi");
  pinMode(fwdRightPin, OUTPUT);
  pinMode(bwdRightPin, OUTPUT);
  pinMode(fwdLeftPin, OUTPUT);
  pinMode(bwdLeftPin, OUTPUT);

  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);

  randomSeed(analogRead(A0));
  //Serial.begin(9600);
}

void loop() {
  leftObstacle = irRead(irLeftPin);
  rightObstacle = irRead(irRightPin);
  frontObstacle = usRead(trig1Pin,echo1Pin);

  if (BT.available()){
    cmd = (BT.read());
    if (cmd == 'm'){
      if(mode == 0){
        mode = 1;
      } else {
        mode = 0;
      }
    }
  }

  if(mode == 0){
    randomMode();
  } else {
    if(cmd == '1'){//left
      speedLeft -= INC_SPEED;
    } else if(cmd == '2'){//up
      speedLeft += INC_SPEED;
      speedRight += INC_SPEED;
    } else if(cmd == '3'){//right
      speedRight -= INC_SPEED;
    } else if(cmd == '4'){//down
      speedLeft -= INC_SPEED;
      speedRight -= INC_SPEED;
    } else if(cmd == 'e'){//stop
      stopMoving();
      speedLeft = 0;
      speedRight = 0;
    }
    applySpeed();
  }
  
}
void applySpeed(){
  if(speedLeft > MAX_SPEED){
    digitalWrite(bwdLeftPin,LOW);
    analogWrite(fwdLeftPin, MAX_SPEED);
    speedLeft = MAX_SPEED;
  } else if (speedLeft < (MAX_SPEED * -1)){
    digitalWrite(fwdLeftPin,LOW);
    analogWrite(bwdLeftPin, MAX_SPEED);
  } else if(speedLeft >= 0){
    digitalWrite(bwdLeftPin,LOW);
    analogWrite(fwdLeftPin, speedLeft);
  }else{
    digitalWrite(fwdLeftPin,LOW);
    analogWrite(bwdLeftPin, abs(speedLeft));
  }
  if(speedRight > MAX_SPEED){
    digitalWrite(bwdRightPin,LOW);
    analogWrite(fwdRightPin, MAX_SPEED);
    speedRight = MAX_SPEED;
  } else if (speedRight < (MAX_SPEED * -1)){
    digitalWrite(fwdRightPin,LOW);
    analogWrite(bwdRightPin, MAX_SPEED);
  } else if(speedRight >= 0){
    digitalWrite(bwdRightPin,LOW);
    analogWrite(fwdRightPin, speedRight);
  }else{
    digitalWrite(fwdRightPin,LOW);
    analogWrite(bwdRightPin, abs(speedRight));
  }
}

void randomMode(){
  if (leftObstacle == 1){
    stopMoving();
    randNumber = random(300, 600);
    moveBackward(200);
    stopMoving();
    turnRight(randNumber);
    //Serial.println("Left");
  } else if (rightObstacle == 1){
    stopMoving();
    randNumber = random(300, 600);
    moveBackward(200);
    stopMoving();
    turnLeft(randNumber);
    //Serial.println("Right");
  } else if(frontObstacle == 1){
    stopMoving();
    randNumber = random(1,10);
    //Serial.print("Front");
    if(randNumber < 5){
      stopMoving();
      randNumber = random(300, 600);
      moveBackward(200);
      stopMoving();
      turnRight(randNumber);
      //Serial.println(" Turn Right");
    } else {
      stopMoving();
      randNumber = random(300, 600);
      moveBackward(200);
      stopMoving();
      turnLeft(randNumber);
      //Serial.println(" Turn Left");
    }
  } else {
    moveForward();
    //Serial.println("Forward");
  }
  //delay(500);
}

int irRead(int irPin){
  int reading = analogRead(irPin);
  if(reading<500){
    return 1;
  } else {
    return 0;
  }
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
  if (distance < 4){
    return 1;
  } else {
    return 0;
  }
}

void turnLeft(int duration){
  digitalWrite(bwdRightPin,LOW);
  analogWrite(fwdRightPin, 150);
  
  digitalWrite(fwdLeftPin,LOW);
  analogWrite(bwdLeftPin, 150);

  delay(duration);
}

void turnRight(int duration){
  digitalWrite(bwdLeftPin,LOW);
  analogWrite(fwdLeftPin, 150);
  
  digitalWrite(fwdRightPin,LOW);
  analogWrite(bwdRightPin, 150);

  delay(duration);
}

void moveForward(){
  digitalWrite(bwdLeftPin,LOW);
  analogWrite(fwdLeftPin, 150);
  
  digitalWrite(bwdRightPin,LOW);
  analogWrite(fwdRightPin, 150);
}

void moveBackward(int duration){
  digitalWrite(fwdLeftPin,LOW);
  analogWrite(bwdLeftPin, 150);
  
  digitalWrite(fwdRightPin,LOW);
  analogWrite(bwdRightPin, 150);

  delay(duration);
}

void stopMoving(){
  digitalWrite(fwdLeftPin,LOW);
  digitalWrite(bwdLeftPin,LOW);
  digitalWrite(fwdRightPin,LOW);
  digitalWrite(bwdRightPin,LOW);
  delay(100);
}

