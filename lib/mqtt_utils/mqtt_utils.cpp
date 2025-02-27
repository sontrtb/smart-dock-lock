#include "mqtt_utils.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "ui.h"
#include <Arduino.h>
#include "ui.h"
#include "mqtt_utils.h"

// Khai báo callback trước khi khởi tạo client
void callback(char* topic, byte* payload, unsigned int length) {
  printf("Message arrived [");
  
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }
  
  // Xử lý thông điệp nhận được
//   if (messageTemp == "ON") {
//     digitalWrite(LEDpin, HIGH);
//   } else if (messageTemp == "OFF") {
//     digitalWrite(LEDpin, LOW);
//   }
}

void setupMQTT(const char* ssid, const char* password) {
  
  // Thiết lập MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (!client.connected()) {
    String clientId = "sonfedev-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
        client.subscribe(mqtt_topic);
    } else {
       
    }
}
  
  // Kết nối lần đầu
//   reconnect();
}

// void reconnect() {
//   // Thử kết nối lại đến khi thành công
//   int attempts = 0;
//   while (!client.connected() && attempts < 3) {
//     Serial.print("Attempting MQTT connection...");
    
//     // Tạo Client ID ngẫu nhiên
//     String clientId = "ESP32Client-";
//     clientId += String(random(0xffff), HEX);
    
//     if (client.connect(clientId.c_str())) {
//       Serial.println("connected");
//       // Sau khi kết nối thành công, subscribe nếu cần
//       client.subscribe(mqtt_topic);
//     } else {
//       delay(5000);
//       attempts++;
//     }
//   }
// }

void publishMessage(const char* topic, const char* message) {
  if (!client.connected()) {
    reconnect();
  }
  
  if (client.connected()) {
    client.publish(topic, message);
    Serial.print("Published to topic: ");
    Serial.print(topic);
    Serial.print(" - Message: ");
    Serial.println(message);
  } else {
    Serial.println("Failed to publish message, client not connected");
  }
}

void mqttLoop() {
  // Kiểm tra kết nối và xử lý các gói tin MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}