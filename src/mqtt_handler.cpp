#include "mqtt_handler.h"
#include <PubSubClient.h>
#include "ui.h"
#include <ArduinoJson.h>

const int LEDpin = 22;

// MQTT Broker settings
const char *mqtt_server = "mqtt.eclipseprojects.io";
const int mqtt_port = 1883;
const char *client_id = "sonfe123";
const char *mqtt_topic_subscribe = "sonfedev";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long openStartTime = 0;
bool doorOpeningState = false;
unsigned long lastReconnectAttempt = 0; // For non-blocking reconnect

void handleOpen()
{
  digitalWrite(LEDpin, LOW);
  _ui_screen_change(&ui_Screen7, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen7_screen_init);

  openStartTime = millis();
  doorOpeningState = true;
}

void checkDoorState()
{
  if (doorOpeningState && (millis() - openStartTime >= 5000))
  {
    // 5 seconds passed, close door
    digitalWrite(LEDpin, HIGH);
    _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen6_screen_init);
    doorOpeningState = false;
  }
}

// Callback function for MQTT messages
void callback(char *topic, byte *payload, unsigned int length)
{
  if (length >= 256)
    return; // Safety check

  char message[256]; // Fixed buffer size for safety

  // Copy payload into message
  for (int i = 0; i < length && i < 255; i++)
  {
    message[i] = (char)payload[i];
  }

  // Print MQTT value
  printf("MQTT Value: %s\n", message);

  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, message);

  if (error)
  {
    printf("JSON Parsing failed: \n");
    printf(error.c_str());
    return;
  }

  String type = doc["type"];
  String data = doc["data"];

  printf(type.c_str());

  if (type == "OPEN")
  {
    handleOpen();
  }
}

// Non-blocking reconnect
bool tryConnect()
{
  if (mqttClient.connect(client_id))
  {
    mqttClient.subscribe(mqtt_topic_subscribe);
    mqttClient.publish(mqtt_topic_subscribe, "Device connected");
    Serial.printf("MQTT Connected successfully\n");
    return true;
  }
  return false;
}

void setupMQTT()
{
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(callback);

  tryConnect();

  _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen6_screen_init);
}

void handleMQTT()
{
  unsigned long currentMillis = millis();

  if (!mqttClient.connected())
  {
    if (currentMillis - lastReconnectAttempt > 5000)
    {
      lastReconnectAttempt = currentMillis;

      // Attempt to reconnect
      if (tryConnect())
      {
        lastReconnectAttempt = 0;
      }
    }
  }
  else
  {
    // Client connected - process messages
    mqttClient.loop();
  }

  // Check door state without blocking
  checkDoorState();
}