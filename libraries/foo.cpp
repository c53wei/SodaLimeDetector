#include "foo.h"
#include "Arduino.h"

bool colour_detector(double setupred, double setupgreen, double setupblue, double redFrequency, double greenFrequency, double blueFrequency) {
  // Return true if reading is purple
  if (setupred+5<redFrequency && setupgreen+5<greenFrequency && setupblue+5<blueFrequency)
    return true;
  else
    return false;
}
