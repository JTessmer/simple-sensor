#include "WifiUtil.h"

#include "../light/LightUtil.h"

WifiUtil::WifiUtil() {
}

void WifiUtil::connect() {

	WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

	Serial.print("Wifi connecting to ");
	Serial.println(Config::WIFI_SSID);

	this->_flashConnectionStatus();

	Serial.println();
	Serial.println("Wifi Connected Successfully!");
	Serial.print("NodeMCU IP Address: ");
	Serial.println( WiFi.localIP() );

	return;
}

void WifiUtil::_flashConnectionStatus() {

	LightUtil primaryLight(Config::LED_PIN);

	while (WiFi.status() != WL_CONNECTED) {
		primaryLight.quickPulse(2);
		Serial.print(".");
	}

	primaryLight.setBrightnessPercent(1);

	return;
}

WiFiClient WifiUtil::getWifiClient() {
	return this->wifiClient;
}
