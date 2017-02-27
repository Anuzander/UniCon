#include "UCKeyPad.h"
#include "Arduino.h"

UCKeyPad::UCKeyPad(String Keys){
  keys = Keys;
}
int UCKeyPad::getKeyId(){
  int ret = -1;
  boolean reset_lockout = 0;
  if(analogRead(A0)==0){
    key_lockout=0;
  }else{
    delay(20);
    ret=15-(log((analogRead(A0)-183.9)/58.24)/0.1623)+0.5;
    key_lockout=1;
  }
  return ret;
}
char UCKeyPad::getKeyVal(){
  char retv = ' ';
  key = getKeyId();
  if(key!=-1){
    retv = keys[key];
    delay(10);
  }
  return retv;
}

