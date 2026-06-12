#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// functions
void generateNewLevel();
void startGame();
void endGame();
void playSequence();
bool playerInputMatching();
