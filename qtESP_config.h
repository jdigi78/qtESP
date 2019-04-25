#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <MQTTClient.h>

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient wifi;
MQTTClient mqtt(256);
unsigned long oldUptime = 0;

/* ----- DO NOT EDIT ABOVE THIS LINE ------ */

/*  WiFi Network  */
const char* wifi_ssid = "My WiFi";
const char* wifi_pass = "Password";

/*  MQTT Server  */
const char* mqtt_server = "192.168.1.100";
int mqtt_port = 1883; // 1883 default, 8883 SSL
const char* mqtt_user = "";
const char* mqtt_pass = "";