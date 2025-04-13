#include <Arduino.h>
#include <WiFiS3.h>
#include "arduino_secrets.h"  // Store your Wi-Fi credentials here

// Motor control pins
const int motorPin1 = 3;
const int motorPin2 = 4;
const int motorPin3 = 5;
const int motorPin4 = 6;

WiFiUDP Udp;
unsigned int localPort = 2390;  // Local port to listen on
char packetBuffer[255];         // Buffer to hold incoming packets

void forward();
void right();
void left();
void stopMotors(); 

void setup() {
  Serial.begin(115200);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

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
      if (strcmp(packetBuffer, "F") == 0) {
        forward();
      } else if (strcmp(packetBuffer, "L") == 0) {
        left();
      } else if (strcmp(packetBuffer, "R") == 0) {
        right();
      } else if (strcmp(packetBuffer, "S") == 0) {
        stopMotors();
      }
    }
  }
}

void forward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void left() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void right() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void stopMotors() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
