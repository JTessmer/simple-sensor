#include <ESP8266WiFi.h>

#include "../util/Config.h"
#include "../led/Led.h"
#include "Wifi.h"

void Wifi::connect() {
	WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

	Serial.println();
	Serial.printf("Wifi connecting to: %s\n", Config::WIFI_SSID);

	// Wait for Connection...
	while(WiFi.status() != WL_CONNECTED) {
		Led::pulse(Config::PIN_STATUS_LED, 2);
		Serial.print(".");
	}

	// Connection established
	Led::setBrightnessPercent(Config::PIN_STATUS_LED, 10);

	Serial.printf("\nWifi connected to '%s' successfully!\n", Config::WIFI_SSID);
	Serial.print("IP Address: ");
	Serial.println( WiFi.localIP() );
	Serial.print("Mac Address: ");
	Serial.println( WiFi.macAddress() );
	Serial.print("Chip ID: ");
	Serial.println( ESP.getChipId() );

	return;
}

void Wifi::keepAlive() {
	if (WiFi.status() != WL_CONNECTED) {
		Wifi::connect();
	}
}
