# SecureMQTTClient Library

The `SecureMQTTClient` library provides a secure and easy way to connect ESP8266 modules to MQTT brokers over TLS. This library simplifies handling WiFi connections, secure MQTT communications, and time synchronization, making it ideal for IoT projects requiring reliable and secure data transmissions.

## Features

- **WiFi Connection Management:** Automatically handles WiFi connectivity.
- **Time Synchronization:** Synchronizes time with NTP servers to ensure valid TLS transactions.
- **Secure MQTT Communication:** Facilitates encrypted communications over TLS.
- **Automated Reconnections:** Handles reconnections for both WiFi and MQTT.
- **Easy Message Publishing:** Provides a simple interface for publishing messages to MQTT topics.
- **Detailed Error Reporting:** Offers explanations for common MQTT connection issues.

## Prerequisites

- ESP8266 development board (e.g., NodeMCU, Wemos D1, etc.).
- Arduino IDE 1.8.10 or higher.
- ESP8266 board packages installed in the Arduino IDE.
- An MQTT broker that supports TLS.
- SPIFFS formatted with the necessary certificate files (`cert.der`, `private.der`, `ca.der`).

## Installation

Download the library ZIP from this repository and include it in your Arduino IDE via:


## Configuration

Configure the library with your network settings, MQTT server details, and certificate paths:

- **SSID and Password:** WiFi credentials.
- **Server Address and Port:** Address and port number of your MQTT broker.
- **Username and Password:** Credentials for MQTT authentication, if required.
- **Certificate Paths:** Paths to the SSL/TLS certificate files stored in SPIFFS.
- **Publish Channel:** The MQTT topic on which the device will publish messages.
- **NTP Server:** Address of an NTP server for time synchronization.
- **DNS Server:** Optional configuration for a custom DNS server, default is Google's DNS.

## Library Functions

### Constructor

```cpp
SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port,
                 const char* user, const char* mqttPassword, const char* certPath, const char* keyPath,
                 const char* caPath, const char* publishChannel, const char* ntpServer = "pool.ntp.org",
                 const IPAddress& dnsServer = IPAddress(8, 8, 8, 8));


Initializes the library with all necessary configurations.

begin()
Initializes the WiFi connection, synchronizes the time, loads certificates, and connects to the MQTT broker.

loop()
Maintains network connections and handles MQTT client processes. Should be called regularly in the Arduino loop() function to manage connectivity.

publish(const char* message)
Publishes a message to the MQTT topic specified in the constructor.

getLastErrorMessage()
Returns the last error message encountered by the client.

explainMqttError(int rc)
Provides a human-readable explanation of MQTT error codes.

Example Usage
Below is an example demonstrating how to use the SecureMQTTClient:

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

Support
For issues, questions, or contributions, please use the GitHub issues page of this repository.

License
This project is licensed under the MIT License - see the LICENSE file for details.


