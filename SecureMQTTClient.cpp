#include "SecureMQTTClient.h"

SecureMQTTClient::SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port, const char* user, const char* mqttPassword, const char* publishChannel, const char* ntpServer)
: _ssid(ssid), _password(password), _server(server), _port(port), _user(user), _mqttPassword(mqttPassword), _publishChannel(publishChannel), _ntpServer(ntpServer), _timeClient(_ntpUDP, ntpServer)
{
    _client.setServer(server, port);
    _client.setClient(_espClient);
    _timeClient.begin();
}

void SecureMQTTClient::begin() {
    setupWifi();
    setupTime();
    loadCertificates();
    connectMQTT();
}

void SecureMQTTClient::setupWifi() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void SecureMQTTClient::setupTime() {
    while (!_timeClient.update()) {
        _timeClient.forceUpdate();
    }
    _espClient.setX509Time(_timeClient.getEpochTime());
}

void SecureMQTTClient::loadCertificates() {
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    File cert = SPIFFS.open("/cert.der", "r");
    if (_espClient.loadCertificate(cert)) Serial.println("Certificate loaded");
    else Serial.println("Failed to load certificate");

    File privateKey = SPIFFS.open("/private.der", "r");
    if (_espClient.loadPrivateKey(privateKey)) Serial.println("Private key loaded");
    else Serial.println("Failed to load private key");

    File ca = SPIFFS.open("/ca.der", "r");
    if (_espClient.loadCACert(ca)) Serial.println("CA loaded");
    else Serial.println("Failed to load CA");
}

void SecureMQTTClient::connectMQTT() {
    while (!_client.connected()) {
        if (_client.connect("ESP8266Client", _user, _mqttPassword)) {
            Serial.println("Connected to MQTT");
        } else {
            delay(5000);
        }
    }
}

void SecureMQTTClient::publish(const char* message) {
    if (!_client.connected()) connectMQTT();
    _client.publish(_publishChannel, message);
}

void SecureMQTTClient::loop() {
    _client.loop();
}

