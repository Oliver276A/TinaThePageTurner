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

  // Actual Loop
  getDistance();
  Serial.println(distance);


  if ((distance > 5) and (distance < 30)) { // 30 seems to be a reasonable distance to trigger the robot. Also, less than 5cm is excluded because of the turning off mechanism
    
    delay(100); // Wait for one more tick to check if glitching
    getDistance();
    Serial.println(distance);
    if ((distance > 5) and (distance < 30)) { // Not glitching, proceed
      stick.write(0); // First, the stick goes to the horizontal position, ready to lift a page
      delay(250); // Wait for the stick to arrive to the right

      for (int s = 91; s < 100; s ++) { // Slowly increasing speed for best grip
        wheel.write(s);
        delay(250);
      }
      //delay(150);
      wheel.write(90);

      // Then the stick slowly lifts and flips the page
      for(int a = 0; a < 160; a ++) { // For each degree
        stick.write(a);
        delay(10);
      }

      // After the stick arrives on the left, the wheel turns slowly to move the page for next flip
      wheel.write(92);
      delay(2000); // Might make loop longer than desired
      wheel.write(90); // Should be moved to the start of the loop
    }
  }


  // Turning off mechanism
  if ((distance <= 5) and (robotOn = true)) { // If very close, trigger the mechanism

    int j = 0; // Make an integer

    while(j < 6) {
      getDistance(); // Get new distance
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