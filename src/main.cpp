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

// Maintains the current known state of the motion sensor
bool motionWasActive = false;


void setup() {
	Serial.begin(9600);
	Serial.println();

	Led::initialize(Config::PIN_STATUS_LED);
	Led::initialize(Config::PIN_MOTION_LED);
	Motion::initialize(Config::PIN_PIR);
	Light::initialize(Config::PIN_LDR);
	Mqtt::initialize(mqttClient);
}

void loop() {

	//----- Perform Connection Maintenance -----//
	Wifi::keepAlive();
	Mqtt::keepAlive(mqttClient);


	bool motionIsActive = Motion::isMotionActive(Config::PIN_PIR);

	// We'll only act if motion activity has changed
	if (motionIsActive != motionWasActive) {
		motionWasActive = motionIsActive;
		int lightLevel = Light::getLightLevel(Config::PIN_LDR);

		Led::setBrightnessPercent(Config::PIN_MOTION_LED, motionIsActive ? 5 : 0);
		Mqtt::sendMotionStatus(mqttClient, motionIsActive, lightLevel);
	}

}
