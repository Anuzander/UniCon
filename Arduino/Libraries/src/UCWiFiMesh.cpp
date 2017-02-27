#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiServer.h>

#include "UCWiFiMesh.h"

#define SSID_PREFIX         "UniCon"
#define SERVER_IP_ADDR      "192.168.200.1"
#define SERVER_PORT         5555

UCWiFiMesh::UCWiFiMesh(uint32_t chip_id, std::function<String(String)> handler)
: _server(SERVER_PORT)
{
  _chip_id = chip_id;
  _ssid = String( String( SSID_PREFIX ) + String( _chip_id ) );
  _ssid_prefix = String( SSID_PREFIX );
  _handler = handler;
}

void UCWiFiMesh::begin()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP( _ssid.c_str() );
    _server.begin();
}
bool UCWiFiMesh::waitForClient(WiFiClient curr_client, int max_wait)
{
  int wait = max_wait;
  while(curr_client.connected() && !curr_client.available() && wait--)
    delay(3);
  if (WiFi.status() == WL_DISCONNECTED || !curr_client.connected())
    return false;
  
  return true;
}
bool UCWiFiMesh::exchangeInfo(String message, WiFiClient curr_client)
{
  curr_client.println( message.c_str() );

  if (!waitForClient(curr_client, 1000))
    return false;

  String response = curr_client.readStringUntil('\r');
  curr_client.readStringUntil('\n');

  if (response.length() <= 2) 
    return false;
  _handler(response);
  return true;
}
void UCWiFiMesh::connectToNode(String target_ssid, String message)
{
  WiFiClient curr_client;
  WiFi.begin( target_ssid.c_str() );

  int wait = 1500;
  while((WiFi.status() == WL_DISCONNECTED) && wait--)
    delay(3);
  if (WiFi.status() != 3)
    return;
  if (!curr_client.connect(SERVER_IP_ADDR, SERVER_PORT)) 
    return;

  if (!exchangeInfo(message, curr_client))
    return;

  curr_client.stop();
  WiFi.disconnect();
}

void UCWiFiMesh::attemptScan(String message)
{
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; ++i) {
    String current_ssid = WiFi.SSID(i);
    int index = current_ssid.indexOf( _ssid_prefix );
    uint32_t target_chip_id = (current_ssid.substring(index + _ssid_prefix.length())).toInt();
    if (index >= 0 && (target_chip_id < _chip_id)) {
      WiFi.mode(WIFI_STA);
      delay(100);
      connectToNode(current_ssid, message);
      WiFi.mode(WIFI_AP_STA);
      delay(100);
    }
  }
}

void UCWiFiMesh::acceptRequest()
{
  while (true) {
    _client = _server.available();
    if (!_client)
      break;

    if (!waitForClient(_client, 1500)) {
      continue;
    }
    String request = _client.readStringUntil('\r');
    _client.readStringUntil('\n');
    String response = _handler(request);
    if (_client.connected())
      _client.println(response);
  }
}

bool UCWiFiMesh::config(){
  
}

