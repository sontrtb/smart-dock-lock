#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>
#include <WiFi.h>

extern const int LEDpin;
extern unsigned long openStartTime;
extern bool doorOpenin;

// MQTT Broker settings
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* client_id;
extern const char* mqtt_topic_subscribe;

extern PubSubClient mqttClient;

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setupMQTT();
void handleMQTT();
void checkDoorState();
void handleOPen();

#endif // MQTT_HANDLER_H