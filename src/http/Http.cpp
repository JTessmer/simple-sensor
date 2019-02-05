#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#include "../util/Config.h"
#include "Http.h"


void Http::post(bool motionIsActive, int lightLevel) {
	if (!Config::USE_HTTP) return;

	HTTPClient http;

	if ( http.begin(Config::API_PATH) ) {
		StaticJsonBuffer<75> JSONbuffer;
		JsonObject& jsonEncoder = JSONbuffer.createObject();

		jsonEncoder["device_id"] = Config::DEVICE_ID;
		jsonEncoder["motion_active"] = motionIsActive;
		jsonEncoder["light_level"] = lightLevel;

		char jsonMessageBuffer[80];
		jsonEncoder.printTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));

		http.addHeader("Content-Type", "application/json");
		http.POST(jsonMessageBuffer);
		http.writeToStream(&Serial);
		http.end();

	} else {
		Serial.printf("[HTTP] Unable to connect\n");
	}

	return;
}
