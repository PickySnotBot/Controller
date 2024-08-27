// lcd.h
#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <rgb_lcd.h>

// Initialize the LCD library with the numbers of the interface pins
extern rgb_lcd lcd;

// Declare the variables as extern
extern const int numMenuItems;
extern String menuItems[];
extern String stickItems[];
extern String axisItems[];

// Function declarations
void lcd_init();
void updateLCD();
void executeMenuItem(int index);
void displayValue(float value);

#endif // LCD_H
