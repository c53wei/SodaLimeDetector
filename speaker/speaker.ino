#include <Wire.h>
#include <foo.h>
#include "pitches.h"

// Define Slave I2C Address
#define SLAVE_ADDR 9
// Define Slave answer size
#define ANSWERSIZE 5

// Define colour sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Timer controllor for sound playing
unsigned long previousMillisPlay=0;
// Timer controller for serial display
unsigned long previous_serial = 0;

// colour sensor reading declarations
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int setupred = 0;
int setupgreen = 0;
int setupblue = 0;

// colour sensor output declaration
bool light1_purple = false;
bool light2_purple = false;
bool light3_purple = false;

// flashing LED related settings
int led = 10;
bool led_on = false;
bool pulse = false;

// speaker related declarations
int half_note = 2;
int pitch = NOTE_C4;
int speaker = 11;
boolean soundon = false;

// off button settings
int button = 13;
bool lastButton = LOW;
bool currentButton = LOW;


void setup() {
  // Initialize I2C communications as Master
  Wire.begin();
  // Initialize colour sensor reading pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);


  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  setupred = pulseIn(sensorOut, LOW);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  setupgreen = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  setupblue = pulseIn(sensorOut, LOW);
  
  // Initialize alarm reactions
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long current_serial = millis();

  // Write a charactre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();

   // Read response from Slave
  // Read back 5 characters
  Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
  // Add characters to string
  String response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  } 
  light1_purple = (bool)String(response.charAt(0)).toInt();
  light2_purple = (bool)String(response.charAt(1)).toInt();

  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
//  Serial.print("R = ");
//  Serial.print(redFrequency);
//  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
//  Serial.print(" G = ");
//  Serial.print(greenFrequency);
//  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
//  Serial.print(" B = ");
//  Serial.println(blueFrequency);
  
  light3_purple = colour_detector(setupred, setupgreen, setupblue, redFrequency, greenFrequency, blueFrequency);
//  if (colour_detector(setupred, setupgreen, setupblue, redFrequency, greenFrequency, blueFrequency)) 
//  {
//    Serial.println("PURPLE");
//  }
//  
  if(current_serial - previous_serial > 1000)
  {
    print_results_sensor(current_serial);
  }
  
  // MODE 1: 1/2 Depletion --> Turn LED on
  if(light1_purple)
  {
    digitalWrite(led, true);
  }
  // MODE 2: 2/3 depletion --> Flash LED
  if(light2_purple)
  {
    pulse = true;
  }
  // MODE 3: 100 % Depletion --> Flash LED & alarm  
  if(light3_purple)
  {
    pulse = true;
    soundon = true;
  }
  // Debounce button
  currentButton = debounce(lastButton);
  // Revert to MODE 0: Everything off if button pressed
  if(lastButton == LOW && currentButton == HIGH) {
      soundon = false;
      pulse = false;
      led_on = false;
      digitalWrite(led, false);
  }
  lastButton = currentButton;
  // Execute mode actions configured above
  // Only applicable for MODE 2 & 3
  // Controls LED flashing
  led_on = play(soundon, pulse, led_on);


}


bool play(boolean soundon, boolean pulse, boolean led_on){
  unsigned long currentMillis = millis();
  if(pulse)
  {
    digitalWrite(led, led_on);

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / half_note;


    
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 2.0;
    
    if ((unsigned long)(currentMillis - previousMillisPlay) >= pauseBetweenNotes) {
      led_on = !led_on;
      if(soundon)
      {
        tone(speaker, pitch, noteDuration);
      }

      previousMillisPlay = currentMillis;
    }

    // stop the tone playing:

    noTone(8);

  
  return led_on;
}}


bool debounce(boolean last) {
  bool current = digitalRead(button);
  if (last != current) {
    delay(5);
    current = digitalRead(button);
  }
  return current;
  
}


bool print_results_sensor(long current_serial) {
    
    Serial.print(light1_purple);
    Serial.print('\t');
    Serial.print(light2_purple);
    Serial.print('\t');
    Serial.print(light3_purple);
    Serial.println();

    previous_serial = current_serial;
}
