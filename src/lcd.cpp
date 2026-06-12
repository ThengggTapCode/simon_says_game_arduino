#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdInit() {
    lcd.init();
    lcd.backlight();
}
void lcdGreet() {
    lcd.print("SIMON SAYS GAME");
    lcd.setCursor(0,1);
    lcd.print("-Welcome!-");
}
void lcdClear() {
    lcd.clear();
}
void lcdPrintLevel(int currentLevel) {
    lcd.print("Level: ");
    lcd.print(currentLevel);
}
void lcdPrintLevelResult(bool pass) {
    lcd.setCursor(0,1);
    if (pass)
        lcd.print("-CORRECT!-");
    else
        lcd.print("-INCORRECT!-");
}
void lcdPrintGameResult(bool gameOver) {
    if (gameOver) {
        lcd.print("GAME OVER!");
        lcd.setCursor(0,1);
        lcd.print("-Try again!-");
    }
    else {
        lcd.print("YOU WON!");
        lcd.setCursor(0,1);
        lcd.print("-Execellent!-");
    }
}