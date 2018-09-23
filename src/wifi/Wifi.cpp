#include <ESP8266WiFi.h>

#include "../util/Config.h"
#include "../led/Led.h"
#include "Wifi.h"

void Wifi::connect() {
	WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);

	Serial.println();
	Serial.print("Wifi connecting to: ");
	Serial.print(Config::WIFI_SSID);

	// Wait for Connection...
	while(WiFi.status() != WL_CONNECTED) {
		Led::pulse(Config::PIN_STATUS_LED, 2);
		Serial.print(".");
	}

	// Connection established
	Led::setBrightnessPercent(Config::PIN_STATUS_LED, 10);

	Serial.println();
	Serial.print("Wifi connected to '");
	Serial.print(Config::WIFI_SSID);
	Serial.println("' successfully!");
	Serial.print("IP Address: ");
	Serial.println( WiFi.localIP() );
	Serial.print("Mac Address: ");
	Serial.println( WiFi.macAddress() );
	Serial.print("Chip ID: ");
	Serial.println( ESP.getChipId() );

	return;
}
