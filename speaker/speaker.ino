#include "pitches.h"

// photoresistor (colour sensor stub) 
int vreader = A0;
double light = 0;

// flashing LED related settings
int led = 4;
bool led_on = false;
bool pulse = false;

// speaker related declarations
int half_note = 2;
int pitch = NOTE_C4;
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
  light = analogRead(vreader);
  Serial.println(light);
  // MODE 1: 1/2 Depletion --> Turn LED on
  if(light > 400 & light < 500)
  {
    digitalWrite(led, true);
  }
  // MODE 2: 2/3 depletion --> Flash LED
  else if(light > 300 & light < 400)
  {
    pulse = true;
    digitalWrite(led, true);
  }
  // MODE 3: 100 % Depletion --> Flash LED & alarm  
  else if(light < 300)
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
      digitalWrite(led, false);
  }
  lastButton = currentButton;
  // Execute mode actions configured above
  play(soundon, pulse, led_on);
  // Only applicable for MODE 2 & 3
  // Controls LED flashing
  led_on = !led_on;
}

void play(boolean soundon, boolean pulse, boolean led_on){
  if(pulse)
  {
    digitalWrite(led, led_on);

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / half_note;

    if(soundon)
    {
      tone(9, pitch, noteDuration);
    }
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }
}

boolean debounce(boolean last) {
  boolean current = digitalRead(button);
  if (last != current) {
    delay(5);
    current = digitalRead(button);
  }
  return current;
  
}



  

  
