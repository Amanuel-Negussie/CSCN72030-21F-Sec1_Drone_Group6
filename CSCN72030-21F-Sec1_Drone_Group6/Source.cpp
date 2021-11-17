
#include <iostream>
#include "batteryWater.h"
#include "Alert.h"
#include "Weather.h"

int main() {


	try {
		/*for (int i = 0; i < 10; i++)
		Alert a = Alert(111);*/
		getAlertLog();
		Weather w = Weather("Sunny");
		w.displayWeather();
	} catch (const char* msg) {
		cout << msg << endl;
	}
	


	return 0;
}