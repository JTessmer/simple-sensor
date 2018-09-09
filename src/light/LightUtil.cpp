#include <Arduino.h>

#include "LightUtil.h"

LightUtil::LightUtil(int ledPin) {
	this->ledPin = ledPin;
}

void LightUtil::init() {
	pinMode(this->ledPin, OUTPUT);

	// Reset LED to off state
	analogWrite(this->ledPin, 0);

	return;
}

void LightUtil::setBrightnessPercent(float percent) {

	int analogValue = static_cast<int>(255 * percent);
	analogWrite(this->ledPin, analogValue);

	return;
}

void LightUtil::quickPulse(int repeatTimes) {

	for (int i = 0; i < repeatTimes; i++) {
		this->setBrightnessPercent(0);
		delay(125);
		this->setBrightnessPercent(0.25);
		delay(125);
	}

	return;
}
