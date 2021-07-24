#include "pitches.h"

unsigned long previousMillisPlay=0;

// photoresistor (colour sensor stub) 
int vreader1 = A0;
double light1 = 0;
bool light1_purple = false;
int vreader2 = A2;
double light2 = 0;
bool light2_purple = false;

// light calibration values
double purple = 600;
double normal_light_conditions = 800;

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
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // take photoresistor reading (to be replaced with colour sensor)
  light1 = analogRead(vreader1);
  light2 = analogRead(vreader2);
  Serial.print(light1);
  Serial.print('\t');
  Serial.print(light2);
  Serial.println();

  light1_purple =  colour_detector(light1);
  light2_purple = colour_detector(light2);
  // MODE 1: 1/2 Depletion --> Turn LED on
  if(light1_purple)
  {
    digitalWrite(led, true);
  }
  
  // MODE 2: 2/3 depletion --> Flash LED
  // Commenting out for now because we only have 2 photoresistors LOL
//  else if(light1 > 300 & light1 < 400)
//  {
//    pulse = true;
//    digitalWrite(led, true);
//  }
  // MODE 3: 100 % Depletion --> Flash LED & alarm  
  if(light2_purple)
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

    int pauseBetweenNotes = noteDuration * 1.30;
    
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

bool colour_detector(double light) {
  // Return true if reading is purple
  return light > purple & light < normal_light_conditions;
}
