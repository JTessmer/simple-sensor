#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>

#include "../util/Const.h"

class MqttUtil {
	private:
		MQTTClient mqttClient;

	public:
		MqttUtil();
		void connect(WiFiClient wifiClient);
		void sendMessage(const char* message);
};
