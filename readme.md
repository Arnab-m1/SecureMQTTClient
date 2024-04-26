# SecureMQTTClient Library

The `SecureMQTTClient` library is designed for ESP8266 modules to establish secure connections to MQTT brokers over TLS. It simplifies the integration of WiFi connectivity, secure MQTT communication, and time synchronization, making it suitable for IoT projects requiring secure and reliable data transmissions.

## Features

- **WiFi Connection Management:** Automatically handles the complexities of managing WiFi connections.
- **Time Synchronization:** Ensures accurate timekeeping with NTP servers for valid TLS transactions.
- **Secure MQTT Communication:** Supports encrypted communications over TLS.
- **Automated Reconnections:** Automatically manages reconnections for both WiFi and MQTT services.
- **Easy Message Publishing:** Provides a straightforward interface for publishing messages to MQTT topics.
- **Detailed Error Reporting:** Delivers comprehensive explanations for common MQTT connection errors.

## Prerequisites

- An ESP8266 development board (e.g., NodeMCU, Wemos D1).
- Arduino IDE 1.8.10 or newer.
- ESP8266 board packages installed within the Arduino IDE.
- An MQTT broker that supports TLS.
- SPIFFS formatted with the required certificate files: `cert.der`, `private.der`, `ca.der`.

## Installation

To install the library:
1. Download the ZIP file from the repository.
2. Add it to your Arduino IDE via `Sketch > Include Library > Add .ZIP Library`.

## Configuration

Configure the library with the following settings:
- **SSID and Password:** Your WiFi credentials.
- **Server Address and Port:** Your MQTT broker's address and port.
- **Username and Password:** MQTT authentication credentials, if required.
- **Certificate Paths:** Locations of SSL/TLS certificate files stored on SPIFFS.
- **Publish Channel:** MQTT topic for publishing messages.
- **NTP Server:** NTP server address for time synchronization, default is `pool.ntp.org`.
- **DNS Server:** Optionally specify a custom DNS server, default is Google's DNS (8.8.8.8).

## Library Functions

- `SecureMQTTClient(...)`: Constructor for initializing the library with necessary configurations.
- `begin()`: Sets up the WiFi connection, synchronizes time, loads certificates, and connects to the MQTT broker.
- `loop()`: Keeps network connections active and manages MQTT client processes. This function should be called regularly within the Arduino `loop()` function.
- `publish(const char* message)`: Publishes a message to the specified MQTT topic.
- `getLastErrorMessage()`: Retrieves the last encountered error message.
- `explainMqttError(int rc)`: Provides explanations for MQTT error codes.

## Example Usage

```cpp
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
For any issues, questions, or contributions, please visit the GitHub issues page associated with this repository.

License
This project is licensed under the MIT License - see the LICENSE file for details.