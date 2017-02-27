#include "UCFileHandler.h"
#include "FS.h"

UCFileHandler::UCFileHandler(){Serial.begin(115200);};

bool UCFileHandler::LoadConfig(WifiConfig* wc){
  bool result = SPIFFS.begin();
  delay(3000);
  Serial.println(" SPIFFS opened: " + result);
  File f = SPIFFS.open("/config.txt", "r");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");    
    File f = SPIFFS.open("/config.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
      return false;
    }
    wc->_Mode="WIFI_AP_STA";
    wc->_Ssid="UniConDefault";
    wc->_Pwd="1234567890";
    wc->_APIP="192.168.100.100";
    wc->_STIP="172.168.100.100";
    result = UCFileHandler::SaveConfig(wc);
    return result;
    } else {
    String line = f.readStringUntil('\n');
    wc->_Mode=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_Ssid=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_Pwd=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_APIP=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_STIP=line.substring(5,line.length());
/*
    Serial.print("MODE=");
    Serial.println(wc->_Mode);
    Serial.print("SSID=");
    Serial.println(wc->_Ssid);
    Serial.print("PASS=");
    Serial.println(wc->_Pwd);
    Serial.print("APIP=");
    Serial.println(wc->_APIP);
    Serial.print("STIP=");
    Serial.println(wc->_STIP);*/
  }
  f.close();
  return result;
}

bool UCFileHandler::SaveConfig(WifiConfig* wc){
  bool result = SPIFFS.begin();
  Serial.println(" SPIFFS opened: " + result);
  File f = SPIFFS.open("/config.txt", "w");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    File f = SPIFFS.open("/config.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
      return false;
    }
  }
  Serial.println("Saving Info...");

  f.print("MODE=");
  f.println(wc->_Mode);
  f.print("SSID=");
  f.println(wc->_Ssid);
  f.print("PASS=");
  f.println(wc->_Pwd);
  f.print("APIP=");
  f.println(wc->_APIP);
  f.print("STIP=");
  f.println(wc->_STIP);
  return true;
}

bool UCFileHandler::SaveDeviceConfig(DeviceConfig* dc){
  bool result = SPIFFS.begin();
  Serial.println(" SPIFFS opened: " + result);
  File f = SPIFFS.open("/deviceconfig.txt", "w");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    File f = SPIFFS.open("/deviceconfig.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
      return false;
    }
  }
  Serial.println("Saving Info...");

  f.print("SWITCHES=");
  f.println(dc->_Switches);
  f.print("SSID=");
  f.println(dc->_Dimmers);
  f.print("PASS=");
  f.println(dc->_KeyPad);
  f.print("APIP=");
  f.println(dc->_IO);
  f.print("STIP=");
  f.println(dc->_Password);
  return true;
}

