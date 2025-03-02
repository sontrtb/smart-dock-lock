#include "mqtt_handler.h"
#include <PubSubClient.h>
#include "ui.h"

const int LEDpin = 22;

// MQTT Broker settings
const char* mqtt_server = "mqtt.eclipseprojects.io";
const int mqtt_port = 1883;
const char* client_id = "sonfe123";
const char* mqtt_topic_subscribe = "sonfedev";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long openStartTime = 0;
bool doorOpeningState = false;
unsigned long lastReconnectAttempt = 0;  // For non-blocking reconnect

void handleOpen() {
  digitalWrite(LEDpin, LOW);
  _ui_screen_change(&ui_Screen7, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen7_screen_init);
  
  openStartTime = millis();
  doorOpeningState = true;
}

void checkDoorState() {
  if (doorOpeningState && (millis() - openStartTime >= 5000)) {
    // 5 seconds passed, close door
    digitalWrite(LEDpin, HIGH);
    _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen6_screen_init);
    doorOpeningState = false;
  }
}

// Callback function for MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  if (length >= 256) return;  // Safety check
  
  char message[256];  // Fixed buffer size for safety
  
  // Copy payload into message
  for (int i = 0; i < length && i < 255; i++) {
    message[i] = (char)payload[i];
  }
  
  // Add null terminator
  message[length < 255 ? length : 255] = '\0';
  
  // Print MQTT value
  Serial.printf("MQTT Value: %s\n", message);
  
  // Compare string properly using strcmp
  if (strcmp(message, "OPEN") == 0) {
    Serial.printf("Executing OPEN command\n");
    handleOpen();
  }
}

// Non-blocking reconnect
bool tryConnect() {
  if (mqttClient.connect(client_id)) {
    mqttClient.subscribe(mqtt_topic_subscribe);
    mqttClient.publish(mqtt_topic_subscribe, "Device connected");
    Serial.printf("MQTT Connected successfully\n");
    return true;
  }
  return false;
}

void setupMQTT() {
  // Configure MQTT client
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(callback);
  
  // Initial connection attempt
  tryConnect();
  
  Serial.printf("MQTT setup completed\n");
  _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen6_screen_init);
}

// Non-blocking MQTT handler for loop() function
void handleMQTT() {
  unsigned long currentMillis = millis();
  
  if (!mqttClient.connected()) {
    // Try to reconnect every 5 seconds without blocking
    if (currentMillis - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = currentMillis;
      
      // Attempt to reconnect
      if (tryConnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected - process messages
    mqttClient.loop();
  }
  
  // Check door state without blocking
  checkDoorState();
}