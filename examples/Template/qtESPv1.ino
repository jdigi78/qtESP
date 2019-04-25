/*
  qtESP v1.0.0
  Development template for ESP8266 based MQTT devices
  Copyright 2019 Joseph DiGiovanni
  https://github.com/jdigi78/qtESP

  Notes:
    + Do not edit this page unless you really know what you're doing (not that I do)
      - I only program as a hobby, so I know this code could be improved somewhere
      - Feel free to make improvements
    + You can manage this device by visiting a few web pages hosted on it:
      - Flash new firmware over WiFi by going to DeviceIP/firmware
      - Reboot by going to DeviceIP/reboot
      - Reset the device and wipe the eeprom by going to DeviceIP/factoryreset
      - all pages are protected by the MQTT username and password
      - replace DeviceIP with the device's assigned IP address
    + The ESP8266 has a bug where it will not come back up from a soft reset after flashing
      - power cycle the device or reset it manually and it will soft reset from then on
*/

bool wifiStatus = false; // Boolean value of current WiFi connection
bool mqttStatus = false; // Boolean value of current MQTT connection
String chipID = String(ESP.getChipId()); // A string containing a unique chip ID number

void setup() {
  // Debug
  Serial.begin(9600);
  Serial.println();
  Serial.println("MAC- " + WiFi.macAddress());
  // WiFi Setup
  WiFi.begin(wifi_ssid, wifi_pass);
  // HTTP Setup
  httpUpdater.setup(&httpServer, "/firmware", mqtt_user, mqtt_pass);
  httpServer.on("/factoryreset", httpReset);
  httpServer.on("/reboot", httpReboot);
  httpServer.begin();
  // MDNS
  MDNS.begin("esptest");
  // MQTT
  mqtt.begin(mqtt_server, mqtt_port, wifi);
  mqtt.onMessage(mqttReceived);
  Setup();
}

void loop() {
  MDNS.update();
  maintainWiFi();
  maintainMQTT();
  // Serve any HTTP requests
  httpServer.handleClient();
  // Run loop code on project page
  mqtt.loop();
  Loop();
}

void maintainWiFi() {
  if (WiFi.status() == WL_CONNECTED && wifiStatus == false) {
    wifiStatus = true;
    Serial.println("WiFi connected with IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(" with RSSI " + String(WiFi.RSSI()));
    wifiConnected();
  }
  if (WiFi.status() != WL_CONNECTED && wifiStatus == true) {
    wifiDisconnected();
    wifiStatus = false;
    Serial.println("WiFi disconnected!");
  }
}

void maintainMQTT() {
  if (mqtt.connected() && mqttStatus == false) {
      Serial.println("Connected to MQTT");
      mqttConnected();
      mqttStatus = true;
  }
  if (!mqtt.connected()) {
    if (mqttStatus == true) {
      Serial.println("Disconnected from MQTT");
      mqttDisconnected();
      mqttStatus = false;
    }
    //  Attempt MQTT connection every 5 seconds
    unsigned long newUptime = millis();
    if (newUptime - oldUptime >= 5000) {
      oldUptime = newUptime;
      mqtt.connect(chipID.c_str(), mqtt_user, mqtt_pass);
    }
  }
}

/* ----- HTTP ----- */

void httpReset() {
  if (!httpAuth())return;
  EEPROM.begin(512);
  // Write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) EEPROM.write(i, 0);
  EEPROM.end();
  httpServer.send(200, "text/plain", "Device has been erased! It will restart in less than a minute");
  delay(200);
  Serial.println("Data erased, restarting...");
  ESP.restart();
}

void httpReboot() {
  if (!httpAuth())return;
  httpServer.send(200, "text/plain", "Device will restart in less than a minute");
  delay(200);
  Serial.println("Restarting...");
  ESP.restart();
}

bool httpAuth() {
  if (!httpServer.authenticate(mqtt_user, mqtt_pass)) {
    httpServer.requestAuthentication();
    return false;
  } else {
    return true;
  }
}
