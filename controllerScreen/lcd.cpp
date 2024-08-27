// lcd.cpp
#include "lcd.h"
#include "encoder.h" // To access menuState

// LCD-specific code
rgb_lcd lcd;

// Define variables
const int numMenuItems = 3;  
String menuItems[numMenuItems] = {"1) Right Stick", "2) Left Stick", "3) Send Data"};
String stickItems[numMenuItems] = {"X axis", "Y axis", "Back"};
String axisItems[numMenuItems] = {"Min Value: ", "Max Value: ", "Back"};

void lcd_init() {
    lcd.begin(16, 2);        
    lcd.setRGB(255, 255, 255); 
    lcd.print(menuItems[0]);
}

void updateLCD() {
    lcd.clear(); 
    switch (menuState) {
        case MAIN_MENU:
            lcd.print(menuItems[menuIndex]);
            break;
        case STICK_MENU:
            lcd.print(stickItems[menuIndex]);
            break;
        case AXIS_MENU:
            lcd.print(axisItems[menuIndex]);
            break;
    }
}

void executeMenuItem(int index) {
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (index) {
        case 0: 
            lcd.setRGB(255, 0, 0);  
            lcd.print("Right Stick");
            delay(2000); // Simulate action
            break;
        case 1: 
            lcd.setRGB(0, 255, 0);  
            lcd.print("Left Stick");
            delay(2000); // Simulate action
            break;
        case 2: 
            lcd.setRGB(0, 0, 255);  
            lcd.print("Sending Data...");
            delay(2000); // Simulate action
            break;
    }
}
