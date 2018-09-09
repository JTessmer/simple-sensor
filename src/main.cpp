#include <Arduino.h>

#include "util/Const.h"
#include "light/LightUtil.h"
#include "wifi/WifiUtil.h"
#include "mqtt/MqttUtil.h"

LightUtil primaryLight(Config::LED_PIN);
WifiUtil systemWifi;
MqttUtil mqttClient;

void setup() {
	primaryLight.init();

	Serial.begin(9600);
	Serial.println();

	systemWifi.connect();

	mqttClient.connect( systemWifi.getWifiClient() );
}

void loop() {

}
