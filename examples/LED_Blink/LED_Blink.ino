/*
  qtESP LED Example
  
  This example displays MQTT connection status via the LED pin specified below.
  Sending "ON" or "OFF" to the MQTT topic below will cause the LED to blink
  the device will then publish the command recieved to [mqttTopic]/state

  Copyright 2019 Joseph DiGiovanni
  https://github.com/jdigi78/qtESP
*/

#include <qtESP_config.h>
// Make sure to edit this file in the library folder!

String mqttTopic = "home/bedroom/test";
int LEDpin = 2;

void Setup() {
  // Setup code goes here
  pinMode(LEDpin, OUTPUT);
  LED_OFF();
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
  mqtt.subscribe(mqttTopic);
  LED_ON();
}

void mqttDisconnected() {
  // Called when mqtt connection is lost
  LED_OFF();
}

void mqttReceived(String &topic, String &payload) {
  // Called when mqtt message recieved
  if (payload == "ON" || payload == "OFF") {
    // Blink LED
    LED_OFF();
    delay(100);
    LED_ON();
  }
  // Reply to the server with device status
  mqtt.publish(mqttTopic + "/state" , payload);
}

/* ----- YOUR FUNCTIONS AFTER THIS LINE ----- */

void LED_ON() {
  digitalWrite(LEDpin, LOW);
}

void LED_OFF() {
  digitalWrite(LEDpin, HIGH);
}
