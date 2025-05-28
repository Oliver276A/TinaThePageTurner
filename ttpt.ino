#include <Servo.h>

/* To do
- Buzzing (might be power issue)
*/

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
  stick.write(160); // Stick goes to the left and hold the sheet
}

void loop() {

  getDistance();
  Serial.println(distance);


  if ((distance > 5) and (distance < 30)) { // 30 seems to be a reasonable distance to trigger the robot. Also, less than 5cm is excluded because of the turning off mechanism
    
    delay(100); // Wait for one more tick to check if glitching
    getDistance();
    Serial.println(distance);
    if ((distance > 5) and (distance < 30)) { // Not glitching, proceed
      stick.write(0); // First, the stick goes to the horizontal position, ready to lift a page
      delay(250); // Wait for the stick to arrive to the right

      // Jolts a bit to get grip
      for (int w = 0; w < 8; w ++) {
        wheel.write(130);
        delay(75);
        wheel.write(80);
        delay(25);
      }
      // Wheel turns
      for (int s = 91; s < 100; s ++) { // Slowly increasing speed for best grip
        wheel.write(s);
        delay(100);
      }

      wheel.write(90); // Stop!

      // Then the stick slowly lifts and flips the page
      for(int a = 0; a < 160; a ++) { // For each degree
        stick.write(a);
        delay(10);
      }

    }
  }


  // Turning off mechanism
  if ((distance <= 5) and (robotOn = true)) { // If very close, trigger the mechanism

    int j = 0; // Make an integer

    while(j < 6) {
      getDistance(); // Get new distance
      Serial.println(distance);
      if (distance <= 5) { // Very close
        j ++; // Count six consequetive times (3 seconds)
        delay(500);
      }
      else {break;} // If far again, proceed
    }

    if (j >= 6) {
      stick.write(0); // Stick returns to neutral position
      Serial.println("Turning off!");
      while(true) {} // If more than 3 seconds, shut down
    }
  }
  
  delay(750);
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