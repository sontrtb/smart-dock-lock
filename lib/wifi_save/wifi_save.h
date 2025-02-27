#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

class WiFiSave {
  private:
    int wifiNameAddress;
    int wifiPasswordAddress;
    
  public:
    WiFiSave(int nameAddr = 0, int passAddr = 50);
    
    void saveWiFiNameCredentials(const String &name);
    void saveWiFiPasswordCredentials(const String &password);
    String getWiFiName();
    String getWiFiPassword();
    
  private:
    void writeStringToEEPROM(int addrOffset, const String &strToWrite);
    String readStringFromEEPROM(int addrOffset);
};

#endif