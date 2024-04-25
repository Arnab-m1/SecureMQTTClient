#include <SecureMQTTClient.h>

// Configure your network and MQTT settings
SecureMQTTClient client(
    "YourWiFiSSID", "YourWifiPassword", "mqtt.example.com", 8883,
    "mqttUser", "mqttPassword", "/cert.der", "/private.der", "/ca.der",
    "topic/test"
);

void setup() {
    Serial.begin(9600);
    client.begin(); // Initialize and connect
}

void loop() {
    client.loop(); // Maintain connectivity and handle MQTT
    client.publish("Hello from ESP8266 with secure MQTT!");
    delay(2000); // Publish every 2 seconds
}
