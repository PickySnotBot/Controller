#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
extern const char* ssid;
extern const char* password;
extern const char* mqtt_server;

// WiFi and MQTT objects
extern WiFiClient espClient;
extern PubSubClient client;

// Joystick pins
extern const int leftJoyXPin;
extern const int leftJoyYPin;
extern const int leftJoyButtonPin;
extern const int rightJoyXPin;
extern const int rightJoyYPin;
extern const int rightJoyButtonPin;

// MQTT topic
extern const char* topic;

// Function declarations
void setup_wifi();
void reconnect();
void joystick_control();

#endif // JOYSTICK_H