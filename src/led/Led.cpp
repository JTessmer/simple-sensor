#include <Arduino.h>

#include "Led.h"


void Led::initialize(int ledPin) {
	pinMode(ledPin, OUTPUT);

	// Reset LED to 'off' state
	analogWrite(ledPin, 0);

	return;
}


void Led::setBrightnessPercent(int ledPin, int percent) {
	float percentAsFloat = static_cast<float>(percent / 100.0);
	int analogValue = static_cast<int>(255 * percentAsFloat);

	analogWrite(ledPin, analogValue);

	return;
}


void Led::pulse(int ledPin, int repeatTimes, int maxPercent, int pulseDelay) {
	int halfDelay = static_cast<int>(pulseDelay / 2);

	for (int i = 0; i < repeatTimes; i++) {
		Led::setBrightnessPercent(ledPin, 0);
		delay(halfDelay);
		Led::setBrightnessPercent(ledPin, maxPercent);
		delay(halfDelay);
	}

	return;
}
