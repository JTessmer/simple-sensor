#include "../util/Const.h"

class LightUtil {
	int ledPin;

	public:
		LightUtil(int ledPin);
		void init();

		void setBrightnessPercent(float percent);

		void quickPulse(int repeatTimes);
};
