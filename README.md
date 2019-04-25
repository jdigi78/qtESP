# qtESP v1.0.0

Easy to use Arduino template to make ESP8266 based MQTT devices in seconds

## Getting Started

The idea is simplicity, and with this template anyone with basic Arduino programming knowledge can bridge the gap between an MQTT command and the physical world

Even if you're an experienced programmer, this will drastically improve your ability to create and deploy MQTT devices quickly

### Prerequisites

* [256dpi/arduino-mqtt](https://github.com/256dpi/arduino-mqtt)

```
Put the "arduino-mqtt-master" folder in "Documents\Arduino\libraries" like any other library
```

## Install

Put the "qtESP-master" folder in "Documents\Arduino\libraries"

Thats it! Open the "Template" example in the IDE

## Further Instructions

I tried to make the code as self explanatory as possible, but here are the basics:
* Fill in your WiFi/MQTT credentials in "qtESP_config.h" located in the "qtESP-master" folder
* Type your code for each function on the Template tab

### MQTT API

There's a full explaination of the arduino-mqtt API at [256dpi/arduino-mqtt](https://github.com/256dpi/arduino-mqtt/) but here are the basics:

* **mqtt.subscribe(String topic)** - subscribe to MQTT topic
* **mqtt.unsubscribe(String topic)** - unsubscribe to MQTT topic
* **mqtt.publish(String topic, String payload)** - publish payload to MQTT topic

### Function Definitions

* **Setup()** - code that runs at startup 
* **Loop()** - main code, to run repeatedly
* **mqttConnected()** - when MQTT server is connected (good place to put your subscribe commands)
* **mqttDisonnected()** - when MQTT server is disconnected
* **mqttReceived()** - when MQTT message is received

### Global Variables

* **deviceName** (String) - String with the custom name of the device, this should be unique as its used for mDNS
* **wifiStatus** (Bool) - Boolean value of current WiFi connection
* **mqttStatus** (Bool) - Boolean value of current MQTT connection
* **chipID** (String) - String containing a unique chip ID number via *ESP.getChipId()*

### qtESP_Config.h

These are settings meant to remain the same between all projects like WiFi credentials and MQTT server information

### Remote Management

You can manage this device by visiting a few web pages hosted on it:
* Flash new firmware over WiFi by going to *DeviceIP*/firmware
* Reboot by going to *DeviceIP*/reboot
* Reset the device and wipe the EEPROM by going to *DeviceIP*/factoryreset
* Access debug information at *DeviceIP*/debug

All pages are protected by the MQTT username and password, replace *DeviceIP* with the device's assigned IP address

You can also connect to the device without knowledge of the IP by going to http://*deviceName*.local if your router supports mDNS

## Known Bugs

This is not a bug with my code specifically, but worth mentioning:
The ESP8266 has a bug where it will not come back up from a soft reset after flashing. Power cycle the device or reset it manually and it will soft reset from then on

## Authors

* **Joseph DiGiovanni** - *Initial work* - [jdigi78](https://github.com/jdigi78)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details
