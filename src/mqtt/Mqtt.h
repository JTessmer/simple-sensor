#ifndef mqtt_h
#define mqtt_h

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace Mqtt {
	void initialize(PubSubClient& mqttClient);
	void connect(PubSubClient& mqttClient);
	void sendMessage(PubSubClient& mqttClient, const char* message);
	void sendMotionStatus(PubSubClient& mqttClient, bool motionIsActive, int lightLevel);
	void keepAlive(PubSubClient& mqttClient);
}

#endif
