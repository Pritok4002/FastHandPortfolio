#include <WiFi.h>
#define WiFissid "*****"
#define WiFipassword "*****"


#include <HTTPClient.h> 
HTTPClient http;
String AccureWeatherGetCurl = "http://dataservice.accuweather.com/currentconditions/v1/294006?apikey=weQ7&details=true";
float TemperatureFromAW;
int RelativeHumidityFromAW;
#include <ArduinoJson.h>
JsonDocument doc;

#include <WiFiUdp.h>
WiFiUDP udp;
const char* udpServerIP = "192.168.0.255";  // IP Компа
const int udpServerPort = 55530;           // Порт компа

#include <NTPClient.h>
WiFiUDP NTPudp;
NTPClient timeClient(NTPudp);
time_t EpochTime;
unsigned long EpochTimeHour;


#include <Wire.h>
TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);
#include "SparkFun_ENS160.h"
SparkFun_ENS160 myENS;
SparkFun_ENS160 myENS2;

#include <SparkFun_Qwiic_Humidity_AHT20.h> 
AHT20 humiditySensor;
AHT20 humiditySensor2;



#define WindowSensorPin 10
#define DoorSensorPin 11

uint8_t PcMac[6]{ 0x04, 0x42, 0xLo, 0xL, 0x10, 0x07 };
struct DataToPc {
  time_t Timestamp;      //время по unix
  time_t TimestampHour;  // сколько часов прошло с 1970

  uint16_t ECo2;       // уровень Co2 с датчика в ppm
  uint16_t TVOC;       // уровень TVOC с датчика в ppb
  uint8_t TempIndoor;  // температура в комнате с датчика в градусах по цельсию
  uint8_t HumIndoor;   // влажность в комнате с датчика в процентах

  uint8_t TempOutdoor;  // температура на улице по AccureWeather
  uint8_t HumOutdoor;   // влажность на улице по AccureWeather

  uint8_t flags;         //0-окно открыто? 1-дверь открыта
  uint8_t sensorid;  // номер датчика
};
DataToPc DataStruct;
DataToPc DataStruct2;

uint8_t BufferPointer = 0;
//uint8_t BuffelLastElement = 0;
DataToPc DataToPcBuffer[96];
