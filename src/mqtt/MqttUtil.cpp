#include "MqttUtil.h"

MqttUtil::MqttUtil() {
}

void MqttUtil::connect(WiFiClient wifiClient) {

	this->mqttClient.begin(Config::MQTT_HOST, wifiClient);

	Serial.print("MQTT connecting to ");
	Serial.println(Config::MQTT_HOST);

	while( !this->mqttClient.connect(Config::DEVICE_ID, Config::MQTT_USER, Config::MQTT_PASSWORD) ) {
		Serial.print(".");
		delay(1000);
	}

	Serial.println("\nConnected to MQTT server!");
	this->sendMessage("Test from NodeMCU!");

	return;
}

void MqttUtil::sendMessage(const char* message) {
	this->mqttClient.publish(Config::MQTT_TOPIC, message);
}
