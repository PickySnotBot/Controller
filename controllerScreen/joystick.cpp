#include "joystick.h"

// Replace with your network credentials
const char* ssid = "Yoav";
const char* password = "basketcase95";
const char* mqtt_server = "192.168.0.151"; // Jetson's IP address

// WiFi and MQTT objects
WiFiClient espClient;
PubSubClient client(espClient);

// Joystick pins
const int leftJoyXPin = 34;
const int leftJoyYPin = 35;
const int leftJoyButtonPin = 25;
const int rightJoyXPin = 32;
const int rightJoyYPin = 33;
const int rightJoyButtonPin = 26;

// MQTT topic
const char* topic = "joystick_data";

// Function to connect to WiFi
void setup_wifi() {
    Serial.begin(115200); // Start the serial communication
    Serial.println("Connecting to WiFi...");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to handle MQTT reconnection
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
            client.subscribe("your_topic"); // Replace with your MQTT topic
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

// Function to read and send joystick data over MQTT
void joystick_control() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Read joystick values
    int leftJoyX = analogRead(leftJoyXPin);
    int leftJoyY = analogRead(leftJoyYPin);
    int leftJoyButton = digitalRead(leftJoyButtonPin);

    int rightJoyX = analogRead(rightJoyXPin);
    int rightJoyY = analogRead(rightJoyYPin);
    int rightJoyButton = digitalRead(rightJoyButtonPin);

    // Define the boolean value (0 or 1) to be added at the beginning
    bool statusFlag = true; // You can set this to false (0) or true (1)

    // Pack the values into a buffer
    uint8_t buffer[11];

    buffer[0] = statusFlag ? 1 : 0; // Add the boolean value at the start
    buffer[1] = leftJoyX >> 8;
    buffer[2] = leftJoyX & 0xFF;
    buffer[3] = leftJoyY >> 8;
    buffer[4] = leftJoyY & 0xFF;
    buffer[5] = leftJoyButton;
    buffer[6] = rightJoyX >> 8;
    buffer[7] = rightJoyX & 0xFF;
    buffer[8] = rightJoyY >> 8;
    buffer[9] = rightJoyY & 0xFF;
    buffer[10] = rightJoyButton;

    // Publish the buffer via MQTT
    client.publish(topic, buffer, sizeof(buffer));

    delay(10); // Adjust delay as necessary
}
