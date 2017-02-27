#ifndef UCKeyPad_H
#define UCKeyPad_H
#include "UCTimer.h"
#include "Arduino.h"

class UCKeyPad{
  public:
    UCKeyPad(String Keys);
    int getKeyId();
    char getKeyVal();
    bool keyLockStatus();
    void setKeylock(boolean va);
  private:
    int key;
    boolean key_lockout;
    String keys;
};
#endif


