/*  
  I2C Slave Demo
  i2c-slave-demo.ino
  Demonstrate use of I2C bus
  Slave receives character from Master and responds
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
 
// Include Arduino Wire library for I2C
#include <Wire.h>
#include <foo.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 9
 
// Define Slave answer size
#define ANSWERSIZE 5

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
 
// Define string with response to Master
String answer = "0";

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int setupred = 0;
int setupgreen = 0;
int setupblue = 0;

boolean purple = false;
int val = 1;

void setup() {
 
  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);
  
  // Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  
  // Setup Serial Monitor 
  Serial.begin(9600);
  Serial.println("I2C Slave Demonstration");

  setupred = pulseIn(sensorOut, LOW);
  setupgreen = pulseIn(sensorOut, LOW);
  setupblue = pulseIn(sensorOut, LOW);
}
 
void receiveEvent() {
 
  // Read while data received
  while (0 < Wire.available()) {
    byte x = Wire.read();
  }
  
  // Print to Serial Monitor
  Serial.println("Receive event");
}
 
void requestEvent() {
 
  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response, sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Request event");
}
 
void loop() {
 
  // Time delay in loop
  delay(50);

  redFrequency = pulseIn(sensorOut, LOW);

  greenFrequency = pulseIn(sensorOut, LOW);

  blueFrequency = pulseIn(sensorOut, LOW);

  //Serial.print(redFrequency);

  //Serial.print(greenFrequency);

  //Serial.println(blueFrequency);

  if (colour_detector(setupred, setupgreen, setupblue, redFrequency, greenFrequency, blueFrequency)) 
  {
    answer = "1";
  }
  else 
  {
    answer = "0";
  }

  
}
