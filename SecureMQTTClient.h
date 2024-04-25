#ifndef SecureMQTTClient_h
#define SecureMQTTClient_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <FS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class SecureMQTTClient {
public:
    SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port,
                     const char* user, const char* mqttPassword, const char* certPath, const char* keyPath,
                     const char* caPath, const char* publishChannel, const char* ntpServer = "pool.ntp.org",
                     const IPAddress& dnsServer = IPAddress(8, 8, 8, 8));
    void begin();
    void loop();
    void publish(const char* message);
    const char* getLastErrorMessage();
    static const char* explainMqttError(int rc);

private:
    const char* _ssid;
    const char* _password;
    const char* _server;
    uint16_t _port;
    const char* _user;
    const char* _mqttPassword;
    const char* _certPath;
    const char* _keyPath;
    const char* _caPath;
    const char* _publishChannel;
    const char* _ntpServer;
    IPAddress _dnsServer;
    WiFiClientSecure _espClient;
    PubSubClient _client;
    WiFiUDP _ntpUDP;
    NTPClient _timeClient;
    
    void setupWifi();
    void connectMQTT();
    void setupTime();
    void loadCertificates();
    String _lastError;
};

#endif
