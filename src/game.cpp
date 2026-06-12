#include <Arduino.h>
#include "game.h"
#include "utils.h"

// constexpr int button[4], led[4], note[4];
// constexpr int buzzer;
// constexpr int totalLevel;

uint8_t sequence[totalLevel];
int currentLevel = 0;
bool firstAttempt = true,
    gameOver = false;

void generateNewLevel() {
  sequence[currentLevel] = random(4);
  currentLevel++;
}
void startGame() {
  randomSeed(analogRead(A0));
  gameOver = false;
  // only flashes when it's the first attempt
  if (firstAttempt) {
    int notes[4] = {262, 330, 392, 523};
    buzzAndFlashLed(notes);
  }
  delay(1000);
}
void endGame() {
  currentLevel = 0;
  gameOver = true;

  // light up all leds and buzz
  int notes[4] = {415, 349, 294, 247};
  buzzAndFlashLed(notes);
}
void playSequence() {
  generateNewLevel();
  for (int i=0; i<currentLevel; i++) {
    uint8_t currentLed = sequence[i];
    digitalWrite(led[currentLed], HIGH);
    delay(500);
    digitalWrite(led[currentLed], LOW);
    delay(300);
  }
}
int getButtonIndex() {
  for (int i=0; i<4; i++) {
    int currentButton = button[i],
            currentLed = led[i];
    if (digitalRead(currentButton) == LOW) {
      // debounce
      delay(50);
      if (digitalRead(currentButton) == LOW) {
        digitalWrite(currentLed, HIGH);
        tone(buzzer, ledNote[i], 200); // buzz for 200ms

        // waits until the button is lifted
        while (digitalRead(currentButton) == LOW);

        // debounce
        delay(50);
        digitalWrite(currentLed, LOW);

        // returns button index
        return i;
      }
    }
  }
  return -1;
}
bool playerInputMatching() {
  for (int i=0; i<currentLevel; i++) {
    int currentLed = sequence[i],
            selectedLed = -1;

    while (selectedLed == -1) {
      selectedLed = getButtonIndex();
    }
    if (selectedLed != currentLed)
      return false;
  }
  return true;
}