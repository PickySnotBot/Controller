// conrtollerScreen.ino
#include <Arduino.h>
#include "lcd.h"
#include "encoder.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "joystick.h"

void setup() {
    Serial.begin(9600);
    setup_wifi();
    client.setServer(mqtt_server, 1883);

    pinMode(leftJoyButtonPin, INPUT_PULLUP);
    pinMode(rightJoyButtonPin, INPUT_PULLUP);
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
