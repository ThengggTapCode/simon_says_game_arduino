#include <Arduino.h>
#include "configVariables.h"

uint8_t sequence[totalLevel];
int currentLevel = 0;
bool firstAttempt = true,
    gameOver = false;