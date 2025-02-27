#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

extern WiFiClient espClient;
extern PubSubClient client;

// Các biến cấu hình MQTT
extern char *mqtt_server;
extern int mqtt_port;
extern char *mqtt_topic;
extern int LEDpin;

// Các khai báo hàm
void setupMQTT(const char* ssid, const char* password);
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);
void publishMessage(const char* topic, const char* message);
void mqttLoop();

#endif // MQTT_UTILS_H