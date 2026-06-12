#include <Arduino.h>
#include "utils.h"
#include "configVariables.h"

// set all leds into a specific state
void controlAllLed(uint8_t state) {
  for (int i=0; i<4; i++) {
    digitalWrite(led[i], state);
  }
}
// flash all leds and buzz
void buzzAndFlashLed(int notes[4]) {
  for (int k=0; k<4; k++) {
    controlAllLed(HIGH);
    tone(buzzer, notes[k]);
    if (k != 3)
      delay(500);
    else
      delay(1000);
    controlAllLed(LOW);
    noTone(buzzer);
  }
}