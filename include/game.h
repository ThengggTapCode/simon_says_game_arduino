#pragma once
#include <Arduino.h>

// constants global variables
constexpr uint8_t button[4] = {2,4,6,8},
            led[4] = {3,5,7,9};
constexpr int ledNote[4] = {262, 330, 392, 494};
constexpr uint8_t buzzer = 13;
constexpr int totalLevel = 100;

// non-constant global variables
extern uint8_t sequence[totalLevel];
extern int currentLevel;
extern bool firstAttempt,
            gameOver;

// functions
void generateNewLevel();
void startGame();
void endGame();
void playSequence();
bool playerInputMatching();
