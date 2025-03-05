#include "Co2Monitor.h"


void setup() {
  InitConnections();
}
void loop() {
}

void MainSequence() {
  FillStruct();
  if (IsPcOnline()) {
    for(int i = 0;i<BufferPointer;i++)
    {
      if(SendStructToPC(&DataToPcBuffer[i]))
    }
  }
  delay(1000*60*60);
}

void FillStruct() {
  GetAccuWeatherPayload();
  DataStruct.TempOutdoor = GetTempOutdoor();
  DataStruct.HumOutdoor = GetHumOutdoor();
  DataStruct2.TempOutdoor = DataStruct.TempOutdoor;
  DataStruct2.HumOutdoor = DataStruct.HumOutdoor;


  GetTimeFromNTP();
  DataStruct.Timestamp = GetEpochTime();
  DataStruct.TimestampHour = GetEpochTimeHour();
  DataStruct2.Timestamp = DataStruct.Timestamp;
  DataStruct2.TimestampHour = DataStruct.TimestampHour;

  ReadSensorSequence();
  bitWrite(DataStruct.flags, 0, IsWindowOpen());
  bitWrite(DataStruct.flags, 1, IsDoorOpen());

  DataToPcBuffer[BufferPointer] = DataStruct;
  BufferPointer++;
  DataToPcBuffer[BufferPointer] = DataStruct2;
  BufferPointer++;
}



void InitConnections() {
  Serial.begin(115200);
  Serial.println("Connecting");
  WiFi.begin(WiFissid, WiFipassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(10800);
  udp.begin(55531);
}
void InitDisconnection() {
}

#pragma region AccureWeather
void GetAccuWeatherPayload() { //получить данные с AW
  http.begin(AccureWeatherGetCurl.c_str());
  int AWhttpResponseCode = http.GET();
  if (AWhttpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(AWhttpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    TemperatureFromAW = doc[0]["Temperature"]["Metric"]["Value"];
    Serial.print("Temp = ");
    Serial.println(TemperatureFromAW);
    RelativeHumidityFromAW = doc[0]["RelativeHumidity"];
    Serial.print("hum = ");
    Serial.println(RelativeHumidityFromAW);
  } else {
    Serial.print("Error code: ");
    Serial.println(AWhttpResponseCode);
  }
}
uint8_t GetTempOutdoor() {
  return TemperatureFromAW;
}
uint8_t GetHumOutdoor() {
  return RelativeHumidityFromAW;
}
#pragma endregion

#pragma region NtpTime
void GetTimeFromNTP() { // получить время unix
  timeClient.forceUpdate();
  EpochTime = timeClient.getEpochTime();
  Serial.println(EpochTime);
  EpochTimeHour = EpochTime / 3600;
  Serial.println(EpochTimeHour);
}
time_t GetEpochTime() {  // возвращает unix время{
  return EpochTime;
}
time_t GetEpochTimeHour() {  // возвращает unix время{
  return EpochTimeHour;
}
#pragma endregion

#pragma region SensorValue
void ReadSensorSequence() { // Данные с датчика в структуру
  I2C_1.begin(14, 13);
  I2C_2.begin(26, 27);
  myENS.begin(I2C_1);
  myENS2.begin(I2C_2);
  humiditySensor.begin(I2C_1);
  humiditySensor2.begin(I2C_2);

  myENS.setOperatingMode(SFE_ENS160_STANDARD);
  myENS2.setOperatingMode(SFE_ENS160_STANDARD);
  myENS.getFlags();
  myENS2.getFlags();
  bool flagEns = false;
  bool flagEns2 = false;
  bool flagAht = false;
  bool flagAht2 = false;
  for (int i = 0; i < 10; i++) {
    if (myENS.getFlags() == 0 && !flagEns) {
      DataStruct.TVOC = myENS.getTVOC();
      DataStruct.ECo2 = myENS.getECO2();
      flagEns = true;
    }
    if (myENS2.getFlags() == 0 && !flagEns2) {
      DataStruct2.TVOC = myENS2.getTVOC();
      DataStruct2.ECo2 = myENS2.getECO2();
      flagEns2 = true;
    }
    if (humiditySensor.available() && !flagAht) {
      DataStruct.TempIndoor = humiditySensor.getTemperature();
      DataStruct.HumIndoor = humiditySensor.getHumidity();
      flagAht = true;
    }
    if (humiditySensor2.available() && !flagAht2) {
      DataStruct2.TempIndoor = humiditySensor2.getTemperature();
      DataStruct2.HumIndoor = humiditySensor2.getHumidity();
      flagAht2 = true;
    }
    if (flagEns && flagEns2 && flagAht && flagAht2) {
      goto SensorLoopEnd;  
    }

    delay(1000 * 60);
  }
  if (!flagEns) {
    DataStruct.TVOC = 0 - 1;
    DataStruct.ECo2 = 0 - 1;
  }
  if (!flagEns2) {
    DataStruct2.TVOC = 0 - 1;
    DataStruct2.ECo2 = 0 - 1;
  }
  if (!flagAht) {
    DataStruct.TempIndoor = 0 - 1;
    DataStruct.HumIndoor = 0 - 1;
  }
  if (!flagAht2) {
    DataStruct2.TempIndoor = 0 - 1;
    DataStruct2.HumIndoor = 0 - 1;
  }

SensorLoopEnd:

  I2C_1.end();
  I2C_2.end();
}
bool IsDoorOpen() { 
  return digitalRead(WindowSensorPin);
}
bool IsWindowOpen() {
  return digitalRead(DoorSensorPin);
}
#pragma endregion

bool IsPcOnline() { //Проверка включен ли комп
  String OkMessage = "AreYouAlive\n";
  String IAmOkMessage = "IAmOk\n";
  for (int q = 0; q < 3; q++) {
    udp.beginPacket(udpServerIP, 55530);
    udp.print(OkMessage);
    udp.endPacket();
    for (int i = 0; i < 100; i++) {
      int packetSize = udp.parsePacket();
      if (packetSize == IAmOkMessage.length()) {
        char incomingPacket[IAmOkMessage.length()];
        udp.read(incomingPacket, IAmOkMessage.length());
        Serial.println(String(incomingPacket, IAmOkMessage.length()));
        if (String(incomingPacket, IAmOkMessage.length()) == IAmOkMessage) {
          Serial.println("PcOkIamReady");
          return 1;
        }
      }
      delay(20);
    }
  }
  Serial.println("PcNOReady");
  return 0;
}
bool SendStructToPC(DataToPc *_dat) { //отправка стурктуры на комп и проверка 
  udp.beginPacket(udpServerIP, udpServerPort);
  udp.write((uint8_t *)&PcMac, sizeof(PcMac));
  udp.write((uint8_t *)&_dat, sizeof(DataToPc));
  udp.endPacket();

  byte StructArr[sizeof(DataToPc)];
  memcpy(StructArr, &_dat, sizeof(DataToPc));
  byte combinedArray[sizeof(DataToPc) + 6];
  for (size_t i = 0; i < 6; i++) {
    combinedArray[i] = PcMac[i];
  }
  for (size_t i = 0; i < sizeof(DataToPc); i++) {
    combinedArray[6 + i] = StructArr[i];
  }

  for (int i = 0; i < 100; i++) {
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
      char incomingPacket[50];
      udp.read(incomingPacket, 50);

      if (compareByteArrays((uint8_t *)&incomingPacket, (uint8_t *)&combinedArray, sizeof(DataToPc) + 6)) {
        Serial.println("равны.");
        return true;
      } else {
        Serial.println("не равны.");
        return false;
      }
    }
    delay(20);
  }
  return false;
}
bool compareByteArrays(const byte *array1, const byte *array2, size_t length) {
  for (size_t i = 0; i < length; i++) {
    if (array1[i] != array2[i]) {
      return false;  // Если хотя бы один элемент не равен
    }
  }
  return true;  // Все элементы равны
}