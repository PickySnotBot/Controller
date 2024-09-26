// lcd.cpp
#include "lcd.h"
#include "encoder.h" // To access menuState
#include "joystick.h" 

// LCD-specific code
rgb_lcd lcd;

// Define the booleanValue
bool booleanValue = false;  // Default value, can be true or false

// Define variables
const int numMenuItems = 5;  
const int numSubMenuItems = 3;  
String menuItems[numMenuItems] = {"1) Right Stick", "2) Left Stick", "3) Send Data", "4) Toggle Boolean", "5) Remote Control"};
String stickItems[numSubMenuItems] = {"X axis", "Y axis", "Back"};
String axisItems[numSubMenuItems] = {"Min Value: ", "Max Value: ", "Back"};

void lcd_init() {
    lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
    delay(100);  // Add a small delay
    lcd.setRGB(255, 255, 255);  // Set the backlight color
    lcd.print("Initializing..."); // Optional: Print a test message
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
            lcd.print("Sending Data..."); // Replace with real fuction to send data
            delay(2000); // Simulate action
            break;
        case 3:  // New option for toggling the boolean
            booleanValue = !booleanValue;  // Toggle the boolean value
            lcd.setRGB(255, 255, 0);  
            lcd.print(booleanValue ? "ASV listening: ON" : "ASV listening: OFF");
            delay(2000); // Show the new state
            break;
        case 4:  // New case for remote control
            lcd.setRGB(255, 255, 0);  
            lcd.print("Remote Control");  // Display message

            // Call function to handle remote control functionality
            joystick_control();  // Example function to send data from joystick
            delay(2000); // Simulate action or wait for response
            
            // Wait for button press to return to the main menu
            lcd.clear();
            lcd.print("Press button to");
            lcd.setCursor(0, 1);
            lcd.print("return to menu");

            // Wait until a button is pressed
            while (digitalRead(button_pin)) {
                delay(100);
            }

            // Reset to the main menu
            menuState = MAIN_MENU;
            menuIndex = 0;  // Reset menuIndex to point to the first item
            updateLCD();     // Update LCD to reflect the main menu
            break;
    }
}
