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
    bool LoadConfig(WifiConfig* wc);
    bool SaveConfig(WifiConfig* wc);

  private:
  
};

#endif
