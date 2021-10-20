#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Motor 0 is on the right from the top view. Or we could switch the wires idk
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);

void setup() {
    AFMS.begin();
    Serial.begin(115200);

    // Set default speed: 0 is stopped, 255 is full speed
    // These are the speeds required for the child to go in a straight line
    //motor0->setSpeed(10);
    motor1->setSpeed(90);
}

void loop() {
    // Do your control loop stuff, changing speeds of motors
    // based on IR sensor readings

    // Argument to run could be FORWARD, BACKWARD, or RELEASE
    motor1->run(BACKWARD);
    //motor1->run(BACKWARD);
    delay(5000);
    motor1->run(RELEASE);
    delay(5000);

}
