#include <SecureMQTTClient.h>

// Configuration parameters
const char* ssid = "yourSSID";
const char* password = "yourWifiPassword";
const char* mqttServer = "mqtt.example.com";
const uint16_t mqttPort = 8883;
const char* mqttUser = "user";
const char* mqttPassword = "password";
const char* publishChannel = "topic/test";
const char* ntpServer = "pool.ntp.org";

SecureMQTTClient client(ssid, password, mqttServer, mqttPort, mqttUser, mqttPassword, publishChannel, ntpServer);

void setup() {
    Serial.begin(9600);
    client.begin();
}

void loop() {
    client.loop();
    client.publish("Hello from ESP8266");
    delay(1000);
}
