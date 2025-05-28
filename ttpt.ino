#include <Servo.h>

// Pin Assignment
const int echoPin = 5;
const int trigPin = 6;
const int wheelPin = 9;
const int stickPin = 11;

// Servo objects
Servo stick;
Servo wheel;

// Variables
long duration;
int distance;
bool robotOn = false;

void setup() {

  // Attaching the servos
  stick.attach(stickPin);
  wheel.attach(wheelPin);
  // Clearing the servos
  stick.write(0);
  wheel.write(90);

  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

    // First wait for signal to start
  int i = 0;
  while(i < 6) {
    getDistance();
    if (distance < 5) {
      i ++;
      delay(500);
    }
  }
  robotOn = true;
}

void loop() {

  // Actual Loop
  getDistance();
  Serial.println(distance);



  // Turning off mechanism
  if ((distance < 5) and (robotOn = true)) { // If very close, trigger the mechanism

    int j = 0; // Make an integer

    getDistance(); // Get new distance
    while(j < 6) {
      if (distance <= 5) { // Very close
        j ++; // Count six consequetive times (3 seconds)
        delay(500);
      }
      else {break;} // If far again, proceed
    }

    if (j >= 6) {
      while(true) {} //If more than 3 seconds, shut down
    }
  }
  
  delay(1000);
}

void getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;
}