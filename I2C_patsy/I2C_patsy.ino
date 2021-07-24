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

#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define sensorOut 8

#define Sz 7
#define Sx 6
#define Sy 5
#define Si 4
#define sensoro 3
 
// Define string with response to Master
String answer = "0";
String answer1 = "0";
String a = "";

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int setupred = 0;
int setupgreen = 0;
int setupblue = 0;

int redFrequency1 = 0;
int greenFrequency1 = 0;
int blueFrequency1 = 0;

int setupred1 = 0;
int setupgreen1 = 0;
int setupblue1 = 0;

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

  setupred1 = pulseIn(sensoro, LOW);
  setupgreen1 = pulseIn(sensoro, LOW);
  setupblue1 = pulseIn(sensoro, LOW);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);

  pinMode(Sz, OUTPUT);
  pinMode(Sx, OUTPUT);
  pinMode(Sy, OUTPUT);
  pinMode(Si, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensoro, INPUT);

  digitalWrite(Sz,HIGH);
  digitalWrite(Sx, HIGH);
  digitalWrite(Sy, HIGH);
}
 
void receiveEvent() {
 
  // Read while data received
  while (0 < Wire.available()) {
    byte x = Wire.read();
  }
  
  // Print to Serial Monitor
  //Serial.println("Receive event");
}
 
void requestEvent() {
 
  // Setup byte variable in the correct size

  a = answer + answer1;
  
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)a.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response, sizeof(response));
  
  // Print to Serial Monitor
  //Serial.println("Request event");
}
 
void loop() {
 
  // Time delay in loop
  delay(250);

  redFrequency = pulseIn(sensorOut, LOW);

  greenFrequency = pulseIn(sensorOut, LOW);

  blueFrequency = pulseIn(sensorOut, LOW);

  Serial.print(" R = ");
  Serial.println(redFrequency);

  Serial.print(" G = ");
  Serial.println(greenFrequency);

  Serial.print(" B = ");
  Serial.println(blueFrequency);

  if (colour_detector(setupred, setupgreen, setupblue, redFrequency, greenFrequency, blueFrequency)) 
  {
    answer = "1";
  }
  else 
  {
    answer = "0";
  }

  Serial.println(answer);
  redFrequency1 = pulseIn(sensoro, LOW);

  greenFrequency1 = pulseIn(sensoro, LOW);

  blueFrequency1 = pulseIn(sensoro, LOW);


  //Serial.print(" R = ");
  //Serial.println(redFrequency1);

  //Serial.print(" G = ");
  //Serial.println(greenFrequency1);

  //Serial.print(" B = ");
  //Serial.println(blueFrequency1);

  if (colour_detector(setupred1, setupgreen1, setupblue1, redFrequency1, greenFrequency1, blueFrequency1)) 
  {
    answer1 = "1";
  }
  else 
  {
    answer1 = "0";
  }

  
}
