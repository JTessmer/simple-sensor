#include <ESP8266WiFi.h>

#include "../util/Const.h"


class WifiUtil {
	private:
		WiFiClient wifiClient;

		void _flashConnectionStatus();

	public:
		WifiUtil();
		void connect();
		WiFiClient getWifiClient();
};
