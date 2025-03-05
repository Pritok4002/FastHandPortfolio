#include "TuyaMqttSign/src/TuyaMqttSign.h"
#include "TuyaMqttSign/src/TuyaMqttSign.cpp"
TuyaMqttSign sign;
#include "certfile.h"
#include <ArduinoJson.h>


#define DEBUG

#ifdef ESP32
#include <WiFi.h>  // Библиотека для ESP32
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#endif
#include "esp_system.h"
#include "esp_partition.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "mqtt_client.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"
#include <sys/param.h>

#include "tuyaData.h"
#include "WIifiData.h"
int msgID = 0;
esp_mqtt_client_handle_t client;
void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  initWiFi();
  sign.calculate(productId, deviceId, deviceSecret);
  Serial.println("username: " + sign.getUsername());
  Serial.println("password: " + sign.getPassword());
  Serial.println("MqttClientId: " + sign.getClientId());
  String tuya_ClientID = sign.getClientId();
  String tuya_Password = sign.getPassword();
  String tuya_Username = sign.getUsername();
  mqtt_cfg = {
    .broker = {
      .address{
        .uri = "mqtts://m1.tuyacn.com:8883" },
      .verification{
        .certificate = ca_cert } },
    .credentials = {
      .username = tuya_Username.c_str(),
      .client_id = tuya_ClientID.c_str(),
      .authentication = { .password = tuya_Password.c_str() },
    }
  };
  client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, NULL);
  esp_mqtt_client_start(client);




}
long timer = 0;
void loop() {
 if (millis() - timer >= 5000) { // таймер на millis()
    timer = millis(); // сброс
  String topic = "tylink/" + deviceId + "/thing/property/report";
  unsigned long timestamp = millis();
  int value = analogRead(33);
  String content = String("{\n") + "\t\"msgId\":\"" + msgID++ + "\",\n" + "\t\"time\":" + timestamp + ",\n" + "\t\"data\":{\n" + "\t\t\"battery_percentage\":{\n" + "\t\t\t\"value\":" + value + ",\n" + "\t\t\t\"time\": " + timestamp + "\n" + "\t\t}\n" + "\t}\n" + "}";
  Serial.println(topic);
  Serial.println(content);
  esp_mqtt_client_publish(client, topic.c_str(), content.c_str(), 0, 1, 0);
  }

  //delay(10000);
}


void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi_ssid, WiFi_password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Connected to AP successfully!");
}
void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
  //WiFi.begin(ssid, password);
  initWiFi();
}

String topicReply = "tylink/" + deviceId + "/thing/property/set";
String datafromCloud;
String valineed;
JsonDocument doc;
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
  Serial.println("event handler");
  esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
  esp_mqtt_client_handle_t client = event->client;
  int msg_id;
  switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
      Serial.println("Connected");

      esp_mqtt_client_subscribe(client, topicReply.c_str(), 0);
      break;
    case MQTT_EVENT_DISCONNECTED:
      Serial.println("Disconnected");
      break;
    case MQTT_EVENT_SUBSCRIBED:
      Serial.println("subscribe");
      break;
    case MQTT_EVENT_UNSUBSCRIBED:
      Serial.println("unsubscribe");
      break;
    case MQTT_EVENT_PUBLISHED:
      Serial.println("publish");
      break;
    case MQTT_EVENT_DATA:
      Serial.println("eventdata");
      datafromCloud = String(event->data).substring(0, event->data_len);
      Serial.println(datafromCloud);
      deserializeJson(doc, datafromCloud);
      valineed = doc["data"]["switch_led"].as<String>();
      Serial.println(valineed);
      digitalWrite(2, LOW);
      if(valineed == "true")
      {
        digitalWrite(2, HIGH);
      }
      else if(valineed == "false")
      {
        digitalWrite(2, LOW);
      }
      break;
    case MQTT_EVENT_ERROR:
      Serial.println("eventerror");
      break;
    default:
      Serial.println("otherevent");
      break;
  }
}