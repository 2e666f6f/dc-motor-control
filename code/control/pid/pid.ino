#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

double IRreading0;
double IRreading1;

double m1_multiplier = 5/2;
double a1_threshold = 500; // If the voltage is higher than this it's probably close enough to the tape that we want to turn. Adjust later.

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Motor 0 is on the right from the top view
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);

void setup() {
    AFMS.begin();
    Serial.begin(115200);

    // Set default speed: 0 is stopped, 255 is full speed
    motor0->setSpeed(20);
    motor1->setSpeed(20*m1_multiplier);
}

void loop() {

    if (IRreading0 > threshold) {
      // turn left
      motor0->setSpeed(30); // Adjust relative speeds later, we weren't able to test this yet!!!!!!!!!!!
      motor1->setSpeed(10*m1_multiplier);
    } else if (IRreading1 > threshold) {
      // turn right
      motor0->setSpeed(10);
      motor1->setSpeed(30*m1_multiplier);
    } else {
      // don't turn
      motor0->setSpeed(20);
      motor1->setSpeed(20*m1_multiplier);
    }
    
    // Argument to run could be FORWARD, BACKWARD, or RELEASE
    motor0->run(FORWARD);
    motor1->run(BACKWARD);

}
