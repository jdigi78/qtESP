/*
  qtESP Blank Template

  Copyright 2019 Joseph DiGiovanni
  https://github.com/jdigi78/qtESP
*/

String deviceName = "qtESP"

#include <qtESP_config.h>
// Make sure to edit this file in the library folder!

void Setup() {
  // Setup code goes here
}

void Loop() {
  // Loop code goes here
}

void wifiConnected() {
  // Called when connected to wifi
}

void wifiDisconnected() {
  // Called when wifi connection is lost
}

void mqttConnected() {
  // Called when connected to mqtt
}

void mqttDisconnected() {
  // Called when mqtt connection is lost
}

void mqttReceived(String &topic, String &payload) {
  // Called when mqtt message recieved
}

/* ----- YOUR FUNCTIONS AFTER THIS LINE ----- */
