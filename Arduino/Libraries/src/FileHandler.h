#ifndef Structure_h
#define Structure_h
#include "Arduino.h"
#include "FS.h"

typedef struct{
  String _Mode;
  String _Ssid;
  String _Pwd;
  String _APIP;
  String _STIP;  
}WifiConfig;

class FileHandler{
  public:
    FileHandler();
    bool LoadWifiConfig(WifiConfig* wc);
    bool SaveWifiConfig(WifiConfig* wc);
  
    bool LoadDeviceConfig(DeviceConfig* dc);
    bool SaveDeviceConfig(DeviceConfig* dc);

    bool LoadLog(LogData* ld);
    bool SaveLog(LogData* ld);

  private:
  
};

#endif
