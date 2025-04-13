#include <Arduino.h>

const int motor1Pin1 = 2; //drives top left ouput pin - should be red motor wire
const int motor1Pin2 = 3; //drives bottom left output pin - should be blk motor wire
const int motor1Pin3 = 4; //drives bottom right output pin - should be blK motor wire
const int motor1Pin4 = 5; //drives top right output pin should be red motor wire

char command;

void forward(); 
void left();
void right();
void stopMotors(); 

void setup() {
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT);  // Motor A forward
  pinMode(motor1Pin2, OUTPUT);  // Motor A backward
  pinMode(motor1Pin3, OUTPUT);  // Motor B forward
  pinMode(motor1Pin4, OUTPUT); // Motor B backward
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    switch (command) {
      case 'F':
        forward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        stopMotors();
        break;
    }
  }
}


void forward() {
  digitalWrite(motor1Pin1, HIGH); digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin3, HIGH); digitalWrite(motor1Pin4, LOW);
}

void left() {
  digitalWrite(motor1Pin1, LOW); digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor1Pin3, HIGH); digitalWrite(motor1Pin4, LOW);
}

void right() {
  digitalWrite(motor1Pin1, HIGH); digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin3, LOW); digitalWrite(motor1Pin4, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW); digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin3, LOW); digitalWrite(motor1Pin4, LOW);
}
