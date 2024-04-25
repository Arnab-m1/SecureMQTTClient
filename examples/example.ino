#include <SecureMQTTClient.h>

SecureMQTTClient client(
    "yourSSID", "yourWifiPassword", "mqtt.example.com", 8883, 
    "user", "password", "/cert.der", "/private.der", "/ca.der", 
    "topic/test"
);

void setup() {
    Serial.begin(9600);
    client.begin();
}

void loop() {
    client.loop();
    client.publish("Hello from ESP8266 with secure MQTT!");
    delay(2000); // Publish every 2 seconds
}