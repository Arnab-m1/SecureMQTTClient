#include <SecureMQTTClient.h>

// Configuration parameters for your WiFi and MQTT server
const char* ssid = "YourWiFiSSID";
const char* password = "YourWifiPassword";
const char* mqttServer = "mqtt.example.com";
const uint16_t mqttPort = 8883;
const char* mqttUser = "mqttUser";
const char* mqttPassword = "mqttPassword";
const char* certPath = "/cert.der";
const char* keyPath = "/private.der";
const char* caPath = "/ca.der";
const char* publishChannel = "topic/test";

// Create the SecureMQTTClient instance with the configuration
SecureMQTTClient client(
    ssid, password, mqttServer, mqttPort,
    mqttUser, mqttPassword, certPath, keyPath, caPath,
    publishChannel
);

void setup() {
    Serial.begin(9600); // Start the serial communication
    Serial.println("Initializing connection...");
    client.begin(); // Initialize and connect to WiFi and MQTT
}

void loop() {
    client.loop(); // Maintain connectivity and handle MQTT tasks
    // Publish a message every 2000 milliseconds (2 seconds)
    Serial.println("Publishing message...");
    client.publish("Hello from ESP8266 with secure MQTT!");
    delay(2000); // Delay to avoid spamming messages
}
