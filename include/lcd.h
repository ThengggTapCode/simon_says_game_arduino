#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "configVariables.h"

extern LiquidCrystal_I2C lcd;

void lcdInit();
void lcdClear();
void lcdGreet();
void lcdPrintLevel(int currentLevel);
void lcdPrintLevelResult(bool pass);
void lcdPrintGameResult(bool gameOver);