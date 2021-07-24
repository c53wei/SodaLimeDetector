#include "pitches.h"
#include "foo.h"

// Timer controllor for sound playing
unsigned long previousMillisPlay=0;
// Timer controller for serial display
unsigned long previous_serial = 0;

// photoresistor (colour sensor stub) 
int vreader1 = A1;
double normal_light1 = 0;
double cur_light1 = 0;
bool light1_purple = false;
int vreader2 = A2;
double normal_light2 = 0;
double cur_light2 = 0;
bool light2_purple = false;
int vreader3 = A3;
double normal_light3 = 0;
double cur_light3 = 0;
bool light3_purple = false;

// light calibration values
double purple = 50;

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
  normal_light1 = analogRead(vreader1);
  normal_light2 = analogRead(vreader2);
  normal_light3 = analogRead(vreader3);
  
}

void loop() {
  unsigned long current_serial = millis();
  // take photoresistor reading (to be replaced with colour sensor)
  cur_light1 = analogRead(vreader1);
  cur_light2 = analogRead(vreader2);
  cur_light3 = analogRead(vreader3);
 
  light1_purple =  colour_detector(abs(cur_light1-normal_light1));
  light2_purple = colour_detector(abs(cur_light2-normal_light2));
  light3_purple = colour_detector(abs(cur_light3-normal_light3));

  
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
  // Commenting out for now because we only have 2 photoresistors LOL
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
  Serial.print(cur_light1);
    Serial.print('\t');
    Serial.print(cur_light2);
    Serial.print('\t');
    Serial.print(cur_light3);
    Serial.println();
    
    Serial.print(light1_purple);
    Serial.print('\t');
    Serial.print(light2_purple);
    Serial.print('\t');
    Serial.print(light3_purple);
    Serial.println();

    previous_serial = current_serial;
}
