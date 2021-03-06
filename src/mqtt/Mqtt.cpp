#include "../util/Config.h"
#include "../led/Led.h"
#include "Mqtt.h"

void Mqtt::initialize(PubSubClient &mqttClient) {
	mqttClient.setServer(Config::MQTT_HOST, Config::MQTT_PORT);
}

void Mqtt::connect(PubSubClient& mqttClient) {

	Serial.println();
	Serial.print("MQTT connecting to: ");
	Serial.print(Config::MQTT_HOST);

	while ( !mqttClient.connected() ) {
		if ( !mqttClient.connect(Config::DEVICE_ID, Config::MQTT_USER, Config::MQTT_PASSWORD) ) {
			Serial.println("MQTT failed... retrying in 5s...");
			Led::pulse(Config::PIN_STATUS_LED, 20);
		}
	}

	Serial.println();
	Serial.print("MQTT successfully connected as '");
	Serial.print(Config::DEVICE_ID);
	Serial.print("'!");

	return;
}

void Mqtt::sendMessage(PubSubClient& mqttClient, const char* message) {
	mqttClient.publish(Config::MQTT_TOPIC, message);
}

void Mqtt::sendMotionStatus(PubSubClient& mqttClient, bool motionIsActive, int lightLevel) {
	StaticJsonBuffer<75> JSONbuffer;
	JsonObject& jsonEncoder = JSONbuffer.createObject();

	jsonEncoder["device_id"] = Config::DEVICE_ID;
	jsonEncoder["motion_active"] = motionIsActive;
	jsonEncoder["light_level"] = lightLevel;

	char jsonMessageBuffer[80];
	jsonEncoder.printTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));

	Serial.println();
	Serial.print("Sending Motion event: ");
	Serial.print(jsonMessageBuffer);

	mqttClient.publish(Config::MQTT_TOPIC, jsonMessageBuffer);
}

void Mqtt::keepAlive(PubSubClient& mqttClient) {
	if (mqttClient.connected()) {
		mqttClient.loop();
	} else {
		Mqtt::connect(mqttClient);
	}
}
