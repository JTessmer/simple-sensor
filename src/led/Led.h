#ifndef led_h
#define led_h

namespace Led {
	void initialize(int ledPin);

	void setBrightnessPercent(int ledPin, int percent);
	void pulse(int ledPin, int repeatTimes = 1, int maxPercent = 7, int pulseDelay = 250);
}

#endif
