#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

double IRreading0;
double IRreading1;
double IRreading2;

double m0_multiplier = 2.1; //based of calibration should be 2.11
double m1_multiplier = 4;   //based of calibration should be 5.57
double speedratio = m1_multiplier/m0_multiplier;
double basespeed = 15;
double lowspeed = 10;
double highspeed = 40;

double a0_threshold = 750; // If the voltage is higher than this it's probably close enough to the tape that we want to turn. Adjust later.
double a1_threshold = 650; // For now these are the same but they may need to be different
double a2_threshold = 650; // Yeah

String command = "";

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Motor 0 is on the right from the top view
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);

void setup() {
    AFMS.begin();
    Serial.begin(115200);

    // Set default speed: 0 is stopped, 255 is full speed
    motor0->setSpeed(basespeed);
    motor1->setSpeed(basespeed*speedratio);
}

void loop() {

   // Communication with serial monitor
   if (Serial.available()) {
        char ch = Serial.read();

        if (ch == '\r') {
            parse_command();
            command = "";
        } else {
            command += ch;
        }
    }

    IRreading0 = analogRead(A0);
    IRreading1 = analogRead(A1);
    IRreading2 = analogRead(A2);
    Serial.println("A0: "+ String(IRreading0) +"  A1: " + String(IRreading1));

  
    if (IRreading0 > a0_threshold) {
      // turn left
      motor0->setSpeed(highspeed); // Adjust relative speeds later, we weren't able to test this yet!!!!!!!!!!!
      motor1->setSpeed(lowspeed*speedratio);
    } else if (IRreading1 > a1_threshold) {
      // turn right
      motor0->setSpeed(lowspeed);
      motor1->setSpeed(highspeed*speedratio);
    } else if (IRreading2 < a1_threshold) {
      // all sensors are off the tape =>
      // rotate in place until a sensor finds the tape
      motor0->setSpeed(0);
      motor1->setSpeed(basespeed*speedratio);
    } else {
      // don't turn
      motor0->setSpeed(basespeed);
      motor1->setSpeed(basespeed*speedratio);
    }
    
    // Argument to run could be FORWARD, BACKWARD, or RELEASE
    motor0->run(FORWARD);
    motor1->run(BACKWARD);

}

void parse_command() {
    if (command.startsWith("SET_M0|")) {
       String arg = command.substring(7);
       arg.trim();
       double new_m0_multiplier = arg.toDouble();
       m0_multiplier = new_m0_multiplier;
    } else if (command.startsWith("SET_M1|")) {
       String arg = command.substring(7);
       arg.trim();
       double new_m1_multiplier = arg.toDouble();
       m1_multiplier = new_m1_multiplier;
    } else if (command.startsWith("SET_A0|")) {
       String arg = command.substring(7);
       arg.trim();
       double new_a0_threshold = arg.toDouble();
       a0_threshold = new_a0_threshold;
    } else if (command.startsWith("SET_A1|")) {
       String arg = command.substring(7);
       arg.trim();
       double new_a1_threshold = arg.toDouble();
       a1_threshold = new_a1_threshold;
    } else if (command.startsWith("SET_A2|")) {
       String arg = command.substring(7);
       arg.trim();
       double new_a2_threshold = arg.toDouble();
       a2_threshold = new_a2_threshold;
    } else if (command.startsWith("ADD_SPEED|")) {
       // Add constant to all speeds 
       String arg = command.substring(10);
       arg.trim();
       int added_speed = arg.toInt();
       basespeed += added_speed;
       highspeed += added_speed;
       lowspeed += added_speed;
    } else if (command.startsWith("SUBTRACT_SPEED|")) {
       // Subtract constant from all speeds 
       String arg = command.substring(16);
       arg.trim();
       int subtracted_speed = arg.toInt();
       basespeed -= subtracted_speed;
       highspeed -= subtracted_speed;
       lowspeed -= subtracted_speed;
       Serial.println("");
    } else {
       Serial.println("Unknown command. >:(");
    }

}
