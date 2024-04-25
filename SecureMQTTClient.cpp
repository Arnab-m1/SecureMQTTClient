#include "SecureMQTTClient.h"

SecureMQTTClient::SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port,
                                   const char* user, const char* mqttPassword, const char* certPath, const char* keyPath,
                                   const char* caPath, const char* publishChannel, const char* ntpServer,
                                   const IPAddress& dnsServer)
: _ssid(ssid), _password(password), _server(server), _port(port), _user(user), _mqttPassword(mqttPassword),
  _certPath(certPath), _keyPath(keyPath), _caPath(caPath), _publishChannel(publishChannel), _ntpServer(ntpServer),
  _dnsServer(dnsServer), _timeClient(_ntpUDP, ntpServer) {
    _client.setServer(server, port);
    _client.setClient(_espClient);
    WiFi.hostname("ESP8266-MQTT");
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, dnsServer);
    _timeClient.begin();
}

void SecureMQTTClient::setupWifi() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(_ssid, _password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void SecureMQTTClient::setupTime() {
    while (!_timeClient.update()) {
        _timeClient.forceUpdate();
    }
    _espClient.setX509Time(_timeClient.getEpochTime());
}

void SecureMQTTClient::loadCertificates() {
    if (!SPIFFS.begin()) {
        _lastError = "Failed to mount file system";
        Serial.println(_lastError);
        return;
    }

    File cert = SPIFFS.open(_certPath, "r");
    if (!cert) {
        _lastError = "Certificate file not found";
        Serial.println(_lastError);
        return;
    }
    if (!_espClient.loadCertificate(cert)) {
        _lastError = "Failed to load certificate";
        Serial.println(_lastError);
    }
    cert.close();

    File privateKey = SPIFFS.open(_keyPath, "r");
    if (!privateKey) {
        _lastError = "Private key file not found";
        Serial.println(_lastError);
        return;
    }
    if (!_espClient.loadPrivateKey(privateKey)) {
        _lastError = "Failed to load private key";
        Serial.println(_lastError);
    }
    privateKey.close();

    File ca = SPIFFS.open(_caPath, "r");
    if (!ca) {
        _lastError = "CA file not found";
        Serial.println(_lastError);
        return;
    }
    if (!_espClient.loadCACert(ca)) {
        _lastError = "Failed to load CA";
        Serial.println(_lastError);
    }
    ca.close();
}

void SecureMQTTClient::connectMQTT() {
    while (!_client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (_client.connect("ESP8266Client", _user, _mqttPassword)) {
            Serial.println("connected to MQTT");
        } else {
            Serial.print("failed, rc=");
            Serial.print(_client.state());
            _lastError = explainMqttError(_client.state());
            Serial.print(" (");
            Serial.print(_lastError);
            Serial.println(") try again in 5 seconds");
            delay(5000);
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
        setupWifi();  // Attempt to reconnect WiFi
    }
    if (!_client.connected()) {
        connectMQTT();  // Ensure the MQTT connection is alive
    }
    _client.loop();
}
