#include "../util/Config.h"
#include "../led/Led.h"
#include "Mqtt.h"

void Mqtt::connect(MQTTClient& mqttClient, WiFiClient& wifiClient) {

	mqttClient.begin(Config::MQTT_HOST, wifiClient);

	Serial.println();
	Serial.print("MQTT connecting to: ");
	Serial.print(Config::MQTT_HOST);

	while ( !mqttClient.connect(Config::DEVICE_ID, Config::MQTT_USER, Config::MQTT_PASSWORD) ) {
		Led::pulse(Config::PIN_STATUS_LED, 2);
		Serial.print(".");
	}

	Serial.println();
	Serial.print("MQTT successfully connected as '");
	Serial.print(Config::DEVICE_ID);
	Serial.print("'!");

	return;
}

void Mqtt::sendMessage(MQTTClient mqttClient, const char* message) {
	mqttClient.publish(Config::MQTT_TOPIC, message);
}
