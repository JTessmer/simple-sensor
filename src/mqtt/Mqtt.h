#ifndef mqtt_h
#define mqtt_h

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <MQTTClient.h>

namespace Mqtt {
	void connect(MQTTClient& mqttClient, WiFiClient& wifiClient);
	void sendMessage(MQTTClient mqttClient, const char* message);
}

#endif
