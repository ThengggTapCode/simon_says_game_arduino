#include <Arduino.h>
#include "game.h"
#include "utils.h"
#include "lcd.h"
#include "configVariables.h"

void generateNewLevel() {
  sequence[currentLevel] = random(4);
  currentLevel++;
}
void startGame() {
  randomSeed(analogRead(A0));
  gameOver = false;

  if (firstAttempt) {
    // only init lcd and greets in the first attempt
    lcdInit();
    lcdGreet();
    // only flashes and buzzes when it's the first attempt
    int notes[4] = {262, 330, 392, 523};
    buzzAndFlashLed(notes);
    delay(1000);
  }
  lcdClear();
}
void endGame() {
  // lcd prints level "lose" result
  lcdClear();
  lcdPrintLevel(currentLevel);
  lcdPrintLevelResult(false);
  // light up all leds and buzz
  int notes[4] = {415, 349, 294, 247};
  buzzAndFlashLed(notes);

  currentLevel = 0;
  gameOver = true;
  // lcd prints game over message
  lcdClear();
  lcdPrintGameResult(gameOver);
  delay(2000);
}
void playSequence() {
  lcdClear();
  lcdPrintLevel(currentLevel+1);
  generateNewLevel();
  for (int i=0; i<currentLevel; i++) {
    uint8_t currentLed = sequence[i];
    digitalWrite(led[currentLed], HIGH);
    delay(300);
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
  lcdPrintLevelResult(true);
  return true;
}