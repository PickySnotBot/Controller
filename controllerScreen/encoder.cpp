// encoder.cpp

#include "encoder.h"
#include "lcd.h"  // Include lcd.h to access executeMenuItem and updateLCD

// Define the global variable here
MenuState menuState = MAIN_MENU;

// Define pins used for the encoder
const int pin_clk = 18;
const int pin_dt = 19;
const int button_pin = 12;

// Initialize counter
int counter = 0;  // or set to -1 if you prefer that

// Other global variable definitions
int menuIndex = 0;
int currentStick = -1;
int currentAxis = -1;
float currentValue = 0;
float maxValue = 4096.0;
float minValue = 0.0;
float rightStickMinMax[2][2] = {{minValue, maxValue}, {minValue, maxValue}};
float leftStickMinMax[2][2] = {{minValue, maxValue}, {minValue, maxValue}};
bool adjustingValue = false;

void encoder_init() {
    pinMode(pin_clk, INPUT);
    pinMode(pin_dt, INPUT);
    pinMode(button_pin, INPUT);

    digitalWrite(pin_clk, HIGH);   
    digitalWrite(pin_dt, HIGH);
    digitalWrite(button_pin, HIGH);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Define the wrapMenuIndex function
void wrapMenuIndex() {
    int maxIndex = 0;
    switch (menuState) {
        case MAIN_MENU:
            maxIndex = numMenuItems;
            break;
        case STICK_MENU:
            maxIndex = numMenuItems;
            break;
        case AXIS_MENU:
            maxIndex = numMenuItems;
            break;
    }

    if (menuIndex < 0) {
        menuIndex = maxIndex - 1;
    } else if (menuIndex >= maxIndex) {
        menuIndex = 0;
    }
}

// Define the handleButtonPress function
void handleButtonPress() {
    switch (menuState) {
        case MAIN_MENU:
            if (menuIndex == 2) { 
                executeMenuItem(menuIndex);
            } else {
                currentStick = menuIndex; 
                menuIndex = 0;
                menuState = STICK_MENU;
                updateLCD();  
            }
            break;
            
        case STICK_MENU:
            if (menuIndex == 2) { 
                menuState = MAIN_MENU;
                menuIndex = currentStick;
                currentStick = -1;
                updateLCD();  
            } else {
                currentAxis = menuIndex;
                menuIndex = 0;
                menuState = AXIS_MENU;
                updateLCD();  
            }
            break;
            
        case AXIS_MENU:
            if (menuIndex == 2) { 
                menuState = STICK_MENU;
                menuIndex = currentAxis;
                currentAxis = -1;
                updateLCD();  
            } else {
                setMinMaxValue(menuIndex);
            }
            break;
    }
}

void setMinMaxValue(int minMaxIndex) {
    adjustingValue = true;

    // Map the current min/max value from 0-4096 to -1 to 1
    if (currentStick == 0) { 
        currentValue = mapFloat(rightStickMinMax[currentAxis][minMaxIndex], 0.0, 4096.0, -1.0, 1.0);
    } else if (currentStick == 1) { 
        currentValue = mapFloat(leftStickMinMax[currentAxis][minMaxIndex], 0.0, 4096.0, -1.0, 1.0);
    }

    lcd.clear();
    lcd.print(axisItems[minMaxIndex]);
    lcd.setCursor(10, 1);
    lcd.print(currentValue, 2); // Display mapped value

    float lastDisplayedValue = currentValue;

    while (adjustingValue) {
        int newClk = digitalRead(pin_clk);
        if (newClk != counter) {
            if (digitalRead(pin_dt) != newClk) {
                currentValue += 0.01;
            } else {
                currentValue -= 0.01;
            }

            // Ensure the value stays within the -1 to 1 range
            if (currentValue < -1.0) {
                currentValue = -1.0;
            } else if (currentValue > 1.0) {
                currentValue = 1.0;
            }

            counter = newClk;
        }

        if (currentValue != lastDisplayedValue) {
            lcd.setCursor(axisItems[minMaxIndex].length(), 0); 
            lcd.print("     ");  
            lcd.setCursor(axisItems[minMaxIndex].length(), 0);  
            lcd.print(currentValue, 2); 
            lastDisplayedValue = currentValue;
        }

        if (!digitalRead(button_pin)) {
            delay(200);
            if (!digitalRead(button_pin)) {
                // Map the adjusted value back from -1 to 1 to 0-4096 and store it
                if (currentStick == 0) {  
                    rightStickMinMax[currentAxis][minMaxIndex] = mapFloat(currentValue, -1.0, 1.0, 0.0, 4096.0);
                } else if (currentStick == 1) {  
                    leftStickMinMax[currentAxis][minMaxIndex] = mapFloat(currentValue, -1.0, 1.0, 0.0, 4096.0);
                }

                adjustingValue = false;  
            }
        }
    }

    menuState = STICK_MENU;
    updateLCD();  
}
