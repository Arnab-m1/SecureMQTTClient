#include "SecureMQTTClient.h"

// Constructor to initialize the library with necessary configurations
SecureMQTTClient::SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port,
                                   const char* user, const char* mqttPassword, const char* certPath, const char* keyPath,
                                   const char* caPath, const char* publishChannel, const char* ntpServer,
                                   const IPAddress& dnsServer)
: _ssid(ssid), _password(password), _server(server), _port(port), _user(user), _mqttPassword(mqttPassword),
  _certPath(certPath), _keyPath(keyPath), _caPath(caPath), _publishChannel(publishChannel), _ntpServer(ntpServer),
  _dnsServer(dnsServer), _timeClient(_ntpUDP, ntpServer) {
    _client.setServer(server, port);
    _client.setClient(_espClient);
    initNetwork();
    _timeClient.begin();
}

void SecureMQTTClient::initNetwork() {
    WiFi.hostname("ESP8266-MQTT");
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, _dnsServer);
}

void SecureMQTTClient::setupWifi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi...");
        WiFi.begin(_ssid, _password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void SecureMQTTClient::setupTime() {
    Serial.println("Synchronizing time...");
    while (!_timeClient.update()) {
        _timeClient.forceUpdate();
    }
    _espClient.setX509Time(_timeClient.getEpochTime());
    Serial.println("Time synchronized");
}

void SecureMQTTClient::loadCertificates() {
    if (!SPIFFS.begin()) {
        _lastError = "Failed to mount file system";
        Serial.println(_lastError);
        return;
    }

    if (!loadFile(_certPath, &_espClient.loadCertificate) ||
        !loadFile(_keyPath, &_espClient.loadPrivateKey) ||
        !loadFile(_caPath, &_espClient.loadCACert)) {
        SPIFFS.end();  // Unmount file system after loading certificates
        return;
    }

    SPIFFS.end();  // Unmount file system after loading certificates
}

bool SecureMQTTClient::loadFile(const char* path, bool (WiFiClientSecure::*loadFunc)(File&)) {
    File file = SPIFFS.open(path, "r");
    if (!file) {
        _lastError = String("File not found: ") + path;
        Serial.println(_lastError);
        return false;
    }
    if (!(this->_espClient.*loadFunc)(file)) {
        _lastError = String("Failed to load file: ") + path;
        Serial.println(_lastError);
        file.close();
        return false;
    }
    file.close();
    return true;
}

void SecureMQTTClient::connectMQTT() {
    while (!_client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (_client.connect("ESP8266Client", _user, _mqttPassword)) {
            Serial.println("Connected to MQTT");
        } else {
            Serial.print("Connection failed, rc=");
            Serial.print(_client.state());
            _lastError = explainMqttError(_client.state());
            Serial.print(" (");
            Serial.print(_lastError);
            Serial.println(") trying again in 5 seconds");
            delay(5000); // Consider using non-blocking delay
        }
    }
}

const char* SecureMQTTClient::getLastErrorMessage() {
    return _lastError.c_str();
}

const char* SecureMQTTClient::explainMqttError(int rc) {
    // Provide explanations for common MQTT return codes
    switch (rc) {
        case -4: return "Connection timed out";
        case -3: return "Connection lost";
        case -2: return "Connect failed";
        case -1: return "Disconnected";
        case 0: return "Connected";
        case 1: return "Bad protocol";
        case 2: return "Client ID rejected";
        case 3: return "Server unavailable";
        case 4: return "Bad username or password";
        case 5: return "Not authorized";
        default: return "Unknown error";
    }
}

void SecureMQTTClient::publish(const char* message) {
    if (!_client.connected()) {
        connectMQTT();
    }
    _client.publish(_publishChannel, message);
}

void SecureMQTTClient::loop() {
    if (WiFi.status() != WL_CONNECTED) {
        setupWifi();
    }
    if (!_client.connected()) {
        connectMQTT();
    }
    _client.loop();
}
