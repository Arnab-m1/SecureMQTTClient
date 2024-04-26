# SecureMQTTClient Library

The `SecureMQTTClient` library provides a secure and streamlined way to connect ESP8266 modules to MQTT brokers using TLS encryption. It handles WiFi connections, secure MQTT communications, and time synchronization to ensure reliable and secure data transmissions in IoT projects.

## Features

- **WiFi Connection Management:** Automatically manages WiFi connections with reconnection capabilities.
- **Time Synchronization:** Synchronizes time with NTP servers to support valid TLS transactions.
- **Secure MQTT Communication:** Ensures encrypted communications over TLS.
- **Automated Reconnections:** Handles MQTT reconnections automatically.
- **Easy Message Publishing:** Simplifies publishing messages to MQTT topics.
- **Detailed Error Reporting:** Provides detailed error messages for troubleshooting connection issues.

## Prerequisites

- ESP8266 development board (e.g., NodeMCU, Wemos D1)
- Arduino IDE 1.8.10 or later
- ESP8266 board packages installed in Arduino IDE
- MQTT broker that supports TLS
- SPIFFS formatted with necessary certificate files (`cert.der`, `private.der`, `ca.der`)

## Installation

1. Download the library ZIP from the repository.
2. Open Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library` and select the downloaded file.

## Configuration

Configure the library with your network settings, MQTT server details, and certificate paths:
- **SSID and Password:** Your WiFi credentials.
- **Server Address and Port:** MQTT broker's address and port.
- **Username and Password:** MQTT authentication credentials, if applicable.
- **Certificate Paths:** Locations of SSL/TLS certificate files stored on SPIFFS.
- **Publish Channel:** MQTT topic for message publication.
- **NTP Server:** Address of an NTP server for time synchronization, default is `pool.ntp.org`.
- **DNS Server:** Custom DNS server, default is Google's DNS (8.8.8.8).

## Usage Example

Here's a simple example to demonstrate the usage of the `SecureMQTTClient` library:

```cpp
#include <SecureMQTTClient.h>

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

SecureMQTTClient client(
    ssid, password, mqttServer, mqttPort,
    mqttUser, mqttPassword, certPath, keyPath, caPath,
    publishChannel
);

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing connection...");
    client.begin();
}

void loop() {
    client.loop();
    Serial.println("Publishing message...");
    client.publish("Hello from ESP8266 with secure MQTT!");
    delay(2000);
}


Support
For issues, questions, or contributions, please visit the GitHub issues page of this repository.

License
This project is licensed under the MIT License - see the LICENSE file for details.