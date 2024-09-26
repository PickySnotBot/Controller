// encoder.h
#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h> // Include Arduino core functions

// Declare the enum
enum MenuState { MAIN_MENU, STICK_MENU, AXIS_MENU };

// Declare menuState as extern to avoid multiple definitions
extern MenuState menuState;

// Function declarations...
void encoder_init();
void handleButtonPress();
void setMinMaxValue(int minMaxIndex);
void wrapMenuIndex();

// Declare external variables for the encoder
extern int counter;  // Declaration of counter here
extern int menuIndex;
extern int currentStick;
extern int currentAxis;
extern float currentValue;
extern bool adjustingValue;
extern float rightStickMinMax[2][2];
extern float leftStickMinMax[2][2];
extern const int pin_clk;
extern const int pin_dt;
extern const int button_pin;

#endif // ENCODER_H
