#include <Arduino.h>

#include "Motion.h"

void Motion::initialize(int motionPin) {
	pinMode(motionPin, INPUT);
}

bool Motion::isMotionActive(int motionPin) {
	return digitalRead(motionPin) == 1;
}
