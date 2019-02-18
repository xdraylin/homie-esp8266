#pragma once

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

#include <AsyncMqttClient.h>

enum class HomieEventType : uint8_t {
  STANDALONE_MODE = 1,
  CONFIGURATION_MODE,
  NORMAL_MODE,
  OTA_STARTED,
  OTA_PROGRESS,
  OTA_SUCCESSFUL,
  OTA_FAILED,
  ABOUT_TO_RESET,
  WIFI_CONNECTED,
  WIFI_DISCONNECTED,
  MQTT_READY,
  MQTT_DISCONNECTED,
  MQTT_PACKET_ACKNOWLEDGED,
  READY_TO_SLEEP,
  SENDING_STATISICS
};

struct HomieEvent {
  HomieEventType type;
  /* WIFI_CONNECTED */
  IPAddress ip;
  IPAddress mask;
  IPAddress gateway;
  /* WIFI_DISCONNECTED */
  #ifdef ESP32
  system_event_sta_disconnected_t wifiReason;
  #elif define(ESP8266)
  WiFiDisconnectReason wifiReason;
  #else
  #error Platform not supported
  #endif
  /* MQTT_DISCONNECTED */
  AsyncMqttClientDisconnectReason mqttReason;
  /* MQTT_PACKET_ACKNOWLEDGED */
  uint16_t packetId;
  /* OTA_PROGRESS */
  size_t sizeDone;
  size_t sizeTotal;
};
