#include "pitches.h"

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  8, 8, 8, 8, 8, 8, 8, 8
};

int button = 13;
boolean lastButton = LOW;
boolean currentButton = LOW;
int led = 4;
boolean soundon = false;
boolean ledOn = false;
int vreader = A0;
double light = 0;
double brightness = 0;
bool pulse = false;
bool flash = true;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  light = analogRead(vreader);
  Serial.println(light);
  
  if(light > 400 & light < 500)
  {
    digitalWrite(led, true);
  }

  else if(light > 300 & light < 400)
  {
    pulse = true;
    digitalWrite(led, true);
  }
  else if(light < 300)
  {
    pulse = true;
    soundon = true;
  }

  currentButton = debounce(lastButton);

  if(lastButton == LOW && currentButton == HIGH) {
      soundon = false;
      pulse = false;
      digitalWrite(led, false);
  }
  lastButton = currentButton;
  play(soundon, pulse, flash);
  flash = !flash;
}

boolean debounce(boolean last) {
  boolean current = digitalRead(button);
  if (last != current) {
    delay(5);
    current = digitalRead(button);
  }
  return current;
  
}

void play(boolean soundon, boolean pulse, boolean flash){
  if(pulse)
  {
    digitalWrite(led, flash);

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / 4;

    if(soundon)
    {
      tone(9, NOTE_C4, 4);
    }
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }
}
  


  

  
