// main.cpp
#include "lcd.h"
#include "encoder.h"

void setup() {
    Serial.begin(9600);

    // Initialize LCD and encoder
    lcd_init();
    encoder_init();
}

void loop() {
    int newClk = digitalRead(pin_clk);

    if (newClk != counter) {
        if (digitalRead(pin_dt) != newClk) {
            menuIndex++;
        } else {
            menuIndex--;
        }

        wrapMenuIndex();
        updateLCD();

        counter = newClk;
    }

    if (!digitalRead(button_pin)) {
        delay(200);  
        if (!digitalRead(button_pin)) {
            handleButtonPress();
            while (!digitalRead(button_pin));
        }
    }
}
