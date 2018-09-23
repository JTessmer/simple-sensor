#include <Arduino.h>

#include "Light.h"

void Light::initialize(int lightPin) {
	// No need to set pinMode for an analog pin; they're always INPUT
}

int Light::getLightLevel(int lightPin) {
	int PURE_DARK = 1024;

	int brightness = PURE_DARK - analogRead(lightPin);

	return brightness;
}
