#include "FileHandler.h"
#include "FS.h"

FileHandler::FileHandler(){};

bool FileHandler::LoadWifiConfig(WifiConfig* wc){
  bool result = SPIFFS.begin();
  Serial.println("SPIFFS opened: " + result);
  File f = SPIFFS.open("/configuration.txt", "r");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    // open the file in write mode
    File f = SPIFFS.open("/configuration.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
    }
    // now write five lines in key/value style with  end-of-line characters
    
    wc->_Mode="AP_STA";
    wc->_Ssid="UniConDefault";
    wc->_Pwd="1234567890";
    wc->_APIP="192.168.100.100";
    wc->_STIP="172.168.100.100";
    FileHandler::SaveWifiConfig(wc);
  } else {
    // we could open the file
    //Lets read line by line from the file
    String line = f.readStringUntil('\n');
    wc->_Mode=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_Ssid=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_Pwd=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_APIP=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_STIP=line.substring(6,line.length());
    /*
     * while(f.available()) {
        //Lets read line by line from the file
        String line = f.readStringUntil('\n');
        Serial.println(line);
      }
     */

  }
  f.close();
}

bool FileHandler::SaveWifiConfig(WifiConfig* wc){
  bool result = SPIFFS.begin();
  Serial.println("SPIFFS opened: " + result);
  File f = SPIFFS.open("/configuration.txt", "r");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    // open the file in write mode
    File f = SPIFFS.open("/configuration.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
    }
    // now write five lines in key/value style with  end-of-line characters
    f.print("MODE=");
    f.println(wc->_Mode);
    f.println("SSID=");
    f.println(wc->_Ssid);
    f.println("PWD=");
    f.println(wc->_Pwd);
    f.println("APIP=");
    f.println(wc->_APIP);
    f.println("STIP=");
    f.println(wc->_STIP);
  }
}

bool FileHandler::LoadDeviceConfig(DeviceConfig* wc){
  bool result = SPIFFS.begin();
  Serial.println("SPIFFS opened: " + result);
  File f = SPIFFS.open("/deviceconfiguration.txt", "r");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    // open the file in write mode
    File f = SPIFFS.open("/deviceconfiguration.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
    }
    // now write five lines in key/value style with  end-of-line characters
    
    wc->_Mode="AP_STA";
    wc->_Ssid="UniConDefault";
    wc->_Pwd="1234567890";
    wc->_APIP="192.168.100.100";
    wc->_STIP="172.168.100.100";
    FileHandler::SaveWifiConfig(wc);
  } else {
    // we could open the file
    //Lets read line by line from the file
    String line = f.readStringUntil('\n');
    wc->_Mode=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_Ssid=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_Pwd=line.substring(5,line.length());
    line = f.readStringUntil('\n');
    wc->_APIP=line.substring(6,line.length());
    line = f.readStringUntil('\n');
    wc->_STIP=line.substring(6,line.length());
    /*
     * while(f.available()) {
        //Lets read line by line from the file
        String line = f.readStringUntil('\n');
        Serial.println(line);
      }
     */

  }
  f.close();
}

bool FileHandler::SaveDeviceConfig(DeviceConfig* wc){
  bool result = SPIFFS.begin();
  Serial.println("SPIFFS opened: " + result);
  File f = SPIFFS.open("/deviceconfiguration.txt", "r");
  if (!f) {
    Serial.println("File doesn't exist yet. Creating it");
    // open the file in write mode
    File f = SPIFFS.open("/deviceconfiguration.txt", "w");
    if (!f) {
      Serial.println("file creation failed");
    }
    // now write five lines in key/value style with  end-of-line characters
    f.print("MODE=");
    f.println(wc->_Mode);
    f.println("SSID=");
    f.println(wc->_Ssid);
    f.println("PWD=");
    f.println(wc->_Pwd);
    f.println("APIP=");
    f.println(wc->_APIP);
    f.println("STIP=");
    f.println(wc->_STIP);
  }
}
