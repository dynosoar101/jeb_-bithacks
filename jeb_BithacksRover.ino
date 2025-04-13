#include <Arduino.h>
#include <WiFiS3.h>
#include "arduino_secrets.h"  // Store your Wi-Fi credentials here

// Motor control pins
const int motorPin1 = 2;
const int motorPin2 = 3;
const int motorPin3 = 4;
const int motorPin4 = 5;

// Heart pop up motors
const int heartPin1 = 6;
const int heartPin2 = 7;
const int heartPin3 = 8;
const int heartPin4 = 9;

bool close = true; 

WiFiUDP Udp;
unsigned int localPort = 2390;  // Local port to listen on
char packetBuffer[255];         // Buffer to hold incoming packets

void forward(int motor1, int motor2, int motor3, int motor4);
void backward(int motor1, int motor2, int motor3, int motor4);
void right(int motor1, int motor2, int motor3, int motor4);
void left(int motor1, int motor2, int motor3, int motor4);
void stopMotors(int motor1, int motor2, int motor3, int motor4); 
void extendStick(int motor1, int motor2, int motor3, int motor4);

void setup() {
  Serial.begin(115200);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(heartPin1, OUTPUT);
  pinMode(heartPin2, OUTPUT);
  pinMode(heartPin3, OUTPUT);
  pinMode(heartPin4, OUTPUT);

   //extendStick(heartPin1, heartPin2, heartPin3, heartPin4);
  
  // Connect to Wi-Fi
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");



  Udp.begin(localPort);

}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, sizeof(packetBuffer) - 1);
    if (len > 0) {
      packetBuffer[len] = 0;  // Null-terminate the string
      Serial.println("Received: " + String(packetBuffer));

      // Control motors based on received command
      if (strcmp(packetBuffer, "Too Close") == 0){
        close = true; 
        stopMotors(motorPin1, motorPin2, motorPin3, motorPin4);
        extendStick(heartPin1, heartPin2, heartPin3, heartPin4);
        while (1){}
      }
      else if (strcmp(packetBuffer, "F") == 0) {
        forward(motorPin1, motorPin2, motorPin3, motorPin4);
        stopMotors(heartPin1, heartPin2, heartPin3, heartPin4);
      } else if (strcmp(packetBuffer, "L") == 0) {
        left(motorPin1, motorPin2, motorPin3, motorPin4);
        delay(1000);
        forward(motorPin1, motorPin2, motorPin3, motorPin4);
        delay(500);

        stopMotors(heartPin1, heartPin2, heartPin3, heartPin4);
      } else if (strcmp(packetBuffer, "R") == 0) {
        right(motorPin1, motorPin2, motorPin3, motorPin4);
        delay(300);
        forward(motorPin1, motorPin2, motorPin3, motorPin4);
        delay(500);

        stopMotors(heartPin1, heartPin2, heartPin3, heartPin4);
      } else if (strcmp(packetBuffer, "S") == 0) {
        stopMotors(motorPin1, motorPin2, motorPin3, motorPin4);
        stopMotors(heartPin1, heartPin2, heartPin3, heartPin4);
      }
    }
  }
}

void forward(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void backward(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}


void left(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void right(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

void stopMotors(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

void extendStick(int motor1, int motor2, int motor3, int motor4){
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

