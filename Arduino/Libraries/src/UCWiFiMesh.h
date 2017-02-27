#ifndef __WIFIMESH_H__
#define __WIFIMESH_H__

#include <WiFiClient.h> 
#include <WiFiServer.h>
#include <functional>

class UCWiFiMesh {

private:
  String _ssid;
  String _ssid_prefix;
  uint32_t _chip_id;

  std::function<String(String)> _handler;
  
  WiFiServer  _server;
  WiFiClient  _client;

  void connectToNode(String target_ssid, String message);
  bool exchangeInfo(String message, WiFiClient curr_client);
  bool waitForClient(WiFiClient curr_client, int max_wait);

public:

  
  UCWiFiMesh(uint32_t chip_id, std::function<String(String)> handler);
  void begin();
  void attemptScan(String message);
  void acceptRequest();
  bool config();
};

#endif

