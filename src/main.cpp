#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "led/Led.h"
#include "light/Light.h"
#include "motion/Motion.h"
#include "mqtt/Mqtt.h"
#include "util/Config.h"
#include "wifi/Wifi.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


// Maintains the current known status of the motion sensor
bool motionWasActive = false;

void setup() {
	Serial.begin(9600);
	Serial.println();

	Led::initialize(Config::PIN_STATUS_LED);
	Led::initialize(Config::PIN_MOTION_LED);
	Motion::initialize(Config::PIN_PIR);
	Light::initialize(Config::PIN_LDR);

	Wifi::connect();

	Mqtt::initialize(mqttClient);
}

void loop() {

	// If we've lost our connection, attempt to reconnect
	if (!mqttClient.connected()) {
		Mqtt::connect(mqttClient);
	}
	// Perform keepalive maintenance on MQTT connection
	mqttClient.loop();

	// If we've lost our connection, restart the system and try to reconnect
	// if ( wifiClient.status() != WL_CONNECTED || !mqttClient.connected() ) {
	// 	ESP.restart();
	// }

	bool motionIsActive = Motion::isMotionActive(Config::PIN_PIR);

	// We'll only act if motion activity has changed
	if (motionIsActive != motionWasActive) {
		motionWasActive = motionIsActive;
		int lightLevel = Light::getLightLevel(Config::PIN_LDR);

		Led::setBrightnessPercent(Config::PIN_MOTION_LED, motionIsActive ? 5 : 0);


		StaticJsonBuffer<75> JSONbuffer;
		JsonObject& jsonEncoder = JSONbuffer.createObject();

		jsonEncoder["device_id"] = Config::DEVICE_ID;
		jsonEncoder["motion_active"] = motionIsActive;
		jsonEncoder["light_level"] = lightLevel;

		char jsonMessageBuffer[80];
		jsonEncoder.printTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));

		Serial.println(jsonMessageBuffer);

		mqttClient.publish(Config::MQTT_TOPIC, jsonMessageBuffer);
	}

}
