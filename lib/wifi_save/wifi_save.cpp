#include "wifi_save.h"

WiFiSave::WiFiSave(int nameAddr, int passAddr) {
  wifiNameAddress = nameAddr;
  wifiPasswordAddress = passAddr;
  
  #if defined(ESP8266) || defined(ESP32)
  EEPROM.begin(512);
  #endif
}

void WiFiSave::saveWiFiNameCredentials(const String &name) {
  writeStringToEEPROM(wifiNameAddress, name);
  
  #if defined(ESP8266) || defined(ESP32)
  EEPROM.commit();
  #endif
}

void WiFiSave::saveWiFiPasswordCredentials(const String &password) {
    writeStringToEEPROM(wifiPasswordAddress, password);
    
    #if defined(ESP8266) || defined(ESP32)
    EEPROM.commit();
    #endif
  }

String WiFiSave::getWiFiName() {
  return readStringFromEEPROM(wifiNameAddress);
}

String WiFiSave::getWiFiPassword() {
  return readStringFromEEPROM(wifiPasswordAddress);
}

void WiFiSave::writeStringToEEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String WiFiSave::readStringFromEEPROM(int addrOffset) {
  int len = EEPROM.read(addrOffset);
  String strRead;
  
  for (int i = 0; i < len; i++) {
    strRead += (char)EEPROM.read(addrOffset + 1 + i);
  }
  
  return strRead;
}