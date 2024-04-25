# SecureMQTTClient Library

The `SecureMQTTClient` library is designed for ESP8266 modules to facilitate easy and secure MQTT communications using TLS encryption. This library simplifies the process of setting up WiFi, NTP synchronization, and MQTT connections with secure authentication using certificates. It is suitable for IoT projects requiring secure data transmission to MQTT brokers.

## Features

- Easy WiFi setup
- NTP-based time synchronization
- Secure MQTT connection using TLS/SSL
- Automatic handling of MQTT reconnections
- Simple interface for publishing MQTT messages
- Built-in certificate management

## How It Works

### Initialization

When an instance of `SecureMQTTClient` is created, it requires configuration parameters including network credentials, MQTT server details, and paths to certificate files. These parameters are used throughout the library to establish and maintain secure connections.

### Connecting to WiFi

The library automatically attempts to connect to the specified WiFi network. It continues to retry until the connection is established, providing feedback via the serial output about the connection status.

### Time Synchronization

Time synchronization is crucial for TLS connections, as certificates have valid from and to dates that need to be verified against the current time. The library uses an NTP client to synchronize the device's clock with the specified NTP server.

### Certificate Management

Certificates are loaded from the SPIFFS (SPI Flash File System) on the ESP8266. The library supports loading:
- A client certificate (`cert.der`)
- A private key (`private.der`)
- A CA certificate (`ca.der`)

These files need to be pre-loaded onto the device's file system before they can be used by the library. Proper loading and validation of these files are critical for establishing a trusted and secure TLS connection.

### MQTT Connection

Once the WiFi connection and time synchronization are in place, the library attempts to connect to the MQTT server using the secure client. If the connection is unsuccessful, the library retries until it establishes the connection, reporting any SSL errors encountered during the process.

### Messaging

Users can publish messages to specified MQTT topics using the `publish` method. The library ensures that the device maintains the MQTT connection, automatically reconnecting and resending messages as needed.

## Prerequisites

- ESP8266 development board (e.g., NodeMCU, Wemos D1 etc.)
- Arduino IDE 1.8.10 or higher
- ESP8266 board packages installed in Arduino IDE
- MQTT broker that supports TLS (like Mosquitto configured for TLS)
- SPIFFS formatted and populated with necessary certificate files (`cert.der`, `private.der`, `ca.der`)

## Installation

1. **Download the Library**: Click on `Download ZIP` from this repository and include it in your Arduino IDE.
2. **Install the Library**: Open the Arduino IDE, navigate to `Sketch > Include Library > Add .ZIP Library...` and select the downloaded ZIP file.

## Quick Start

### Configure the Library

Before using the `SecureMQTTClient`, you must configure it with your network and broker settings. Modify the following parameters in your sketch:

- `ssid`: Your WiFi network name
- `password`: Your WiFi network password
- `mqttServer`: The domain or IP address of your MQTT broker
- `mqttPort`: The port on which your MQTT broker is running (commonly 8883 for TLS)
- `mqttUser`: Username for MQTT authentication (if applicable)
- `mqttPassword`: Password for MQTT authentication
- `publishChannel`: MQTT topic to publish messages
- `ntpServer`: NTP server for time synchronization

### Sample Sketch

[Include a simple example here, similar to the previous section]

## Documentation

For more detailed documentation, please refer to the comments in the header and implementation files of the library.

## Support

For issues, questions, or contributions, please use the GitHub issues page of this repository.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
