#ifndef UCFileHandler_h
#define UCFileHandler_h
#include "Arduino.h"
#include "FS.h"
#include "Structure.h"


class UCFileHandler{
  public:
    UCFileHandler();
    bool LoadWiFiConfig(WifiConfig* wc);
    bool SaveWiFiConfig(WifiConfig* wc);

    bool LoadDeviceConfig(DeviceConfig* dc);
    bool SaveDeviceConfig(DeviceConfig* dc);

  private:
  
};

#endif
