#include <foo.h>

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int setupred = 0;
int setupgreen = 0;
int setupblue = 0;

boolean purple = false;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  setupred = pulseIn(sensorOut, LOW);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  setupgreen = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  setupblue = pulseIn(sensorOut, LOW);
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(2000);

  if (colour_detector(setupred, setupgreen, setupblue, redFrequency, greenFrequency, blueFrequency)) 
  {
    Serial.println("PURPLE");
  }
}
