#ifndef TUYA_MQTT_SIGN_H
#define TUYA_MQTT_SIGN_H

#include <Arduino.h>
#include <Crypto.h>
#include <SHA256.h>
#define HASH_SIZE 32
class TuyaMqttSign {
public:
    TuyaMqttSign();

    String getUsername();
    String getPassword();
    String getClientId();
    void calculate(const String& productKey, const String& deviceId, const String& deviceSecret);
    

private:
    String username;
    String password;
    String clientId;
    String hmacSha256(const String& plainText, const String& key);

    
};

#endif // TUYA_MQTT_SIGN_H