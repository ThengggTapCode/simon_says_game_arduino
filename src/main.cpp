#include <Arduino.h>
#include "game.h"

void setup() {
  Serial.begin(9600);
  for (int i=0; i<4; i++) {
    pinMode(button[i], INPUT_PULLUP);
    pinMode(led[i], OUTPUT);
  }
  pinMode(buzzer, OUTPUT);
  startGame();
  firstAttempt = false;
}
void loop() {
  if (!gameOver) {
    playSequence();

    if (!playerInputMatching()) {
      endGame();
      delay(1000);
      return;
    }
    delay(1000);
  }
  else
    startGame();
}