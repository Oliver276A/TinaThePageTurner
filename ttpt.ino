#include <Servo.h>

// Pin Assignment
const int echoPin = 5;
const int trigPin = 6;
const int wheelPin = 11;
const int stickPin = 9;

// Servo objects
Servo stick;
Servo wheel;

// Variables
long duration;
int distance;

void setup() {

  // Attaching the servos
  stick.attach(stickPin);
  wheel.attach(wheelPin);
  // Clearing the servos
  stick.write(0);
  wheel.write(0);

  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.println(distance);
  delay(1000);
}
