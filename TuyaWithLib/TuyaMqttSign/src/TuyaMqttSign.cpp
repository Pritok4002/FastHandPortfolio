#include "TuyaMqttSign.h"

TuyaMqttSign::TuyaMqttSign() : username(""), password(""), clientId("") {}

String TuyaMqttSign::getUsername() {
  return username;
}

String TuyaMqttSign::getPassword() {
  return password;
}

String TuyaMqttSign::getClientId() {
  return clientId;
}

void TuyaMqttSign::calculate(const String& productKey, const String& deviceId, const String& deviceSecret) {
  if (productKey.length() == 0 || deviceId.length() == 0 || deviceSecret.length() == 0) {
    return;
  }
  try {
    unsigned long timestamp = millis();  // Используем millis() для получения времени в миллисекундах
    // MQTT username
    username = deviceId + "|signMethod=hmacSha256,timestamp=" + String(timestamp) + ",secureMode=1,accessType=1";
    // MQTT clientId
    clientId = "tuyalink_" + deviceId;

    String plainPasswd = "deviceId=" + deviceId + ",timestamp=" + String(timestamp) + ",secureMode=1,accessType=1";
    #ifdef DEBUG
    Serial.println("plainPasswd= " + plainPasswd);
    #endif
    // MQTT password
    password = hmacSha256(plainPasswd, deviceSecret);
  } catch (const std::exception& e) {
    #ifdef DEBUG
    Serial.println(e.what());
    #endif
  }
}

String TuyaMqttSign::hmacSha256(const String& plainText, const String& key) {
  uint8_t result[HASH_SIZE];
  String resultString = "";

  hmac<SHA256>(result, HASH_SIZE, key.c_str(), key.length(), plainText.c_str(), plainText.length());
  char buffer[3];  // Два символа для байта и один для нуль-терминатора
  for (size_t i = 0; i < 32; i++) {
    sprintf(buffer, "%02X", result[i]);  // Форматирование с двумя символами
    resultString += buffer;
  }
  resultString.toLowerCase();
  return resultString;
}