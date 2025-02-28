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

void handleOPen() {
  digitalWrite(LEDpin, LOW);
  _ui_screen_change(&ui_Screen7, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen7_screen_init);
  
  // Thay delay bằng cách ghi nhớ thời điểm bắt đầu
  openStartTime = millis();
  doorOpeningState = true;
}

void checkDoorState() {
  if (doorOpeningState && (millis() - openStartTime >= 5000)) {
    // Đã đủ 5 giây, đóng cửa
    digitalWrite(LEDpin, HIGH);
    _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen6_screen_init);
    doorOpeningState = false;
  }
}

// Callback function for MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  
  // Sao chép payload vào message
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  // Thêm null terminator
  message[length] = '\0';
  
  // In ra giá trị MQTT
  printf("MQTT Value: %s\n", message);

  // So sánh chuỗi đúng cách bằng strcmp
  if (strcmp(message, "OPEN") == 0) {
    printf("Executing OPEN command\n");
    handleOPen();
  }
}

void reconnect() {
  // Loop until we're reconnected
  int attempts = 0;
  while (!mqttClient.connected() && attempts < 5) {
    // Attempt to connect
    if (mqttClient.connect(client_id)) {
      mqttClient.subscribe(mqtt_topic_subscribe);
    
      mqttClient.publish(mqtt_topic_subscribe, "Device connected");
      printf("MQTT Connected successfully\n");
    } else {
      attempts++;
      delay(3000);
    }
  }
}

void setupMQTT() {
  // Configure MQTT client
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(callback);
  
  // Try to connect
  if (!mqttClient.connected()) {
    reconnect();
  }
  
  printf("MQTT setup completed\n");
  
  _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen6_screen_init);
}

// This function should be called in your loop() function
void handleMQTT() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}