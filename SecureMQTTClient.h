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
    SecureMQTTClient(const char* ssid, const char* password, const char* server, uint16_t port, const char* user, const char* mqttPassword, const char* publishChannel, const char* ntpServer);
    void begin();
    void loop();
    void publish(const char* message);

private:
    const char* _ssid;
    const char* _password;
    const char* _server;
    uint16_t _port;
    const char* _user;
    const char* _mqttPassword;
    const char* _publishChannel;
    const char* _ntpServer;
    WiFiClientSecure _espClient;
    PubSubClient _client;
    WiFiUDP _ntpUDP;
    NTPClient _timeClient;
    
    void setupWifi();
    void connectMQTT();
    void setupTime();
    void loadCertificates();
};

#endif
