#include <Arduino.h>

#include "Light.h"

void Light::initialize(int lightPin) {
	// No need to set pinMode for an analog pin; they're always INPUT
}

int Light::getLightLevel(int lightPin) {
	// Pure Dark == 0
	// Pure Light == 1024
	int brightness =  analogRead(lightPin);

	return brightness;
}
