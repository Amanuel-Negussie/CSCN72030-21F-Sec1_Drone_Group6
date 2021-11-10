#pragma once

#include <string>

using namespace std;

enum WeatherDescription {

	Sunny,
	Cloudy,
	Overcast,
	Showers,
	Rainstorm,
	Snow

};

ostream& operator << (ostream& stream, WeatherDescription weatherDescription) {
	const string weatherDescriptionString[] = { "Sunny", "Cloudy", "Overcast", "Showers", "Rainstorm", "Snow" };
	return stream << weatherDescriptionString[weatherDescription];
}

class Weather {

	float temperature, precipitationAmount, windSpeed;
	int pop, humidity;
	WeatherDescription weatherDescription;


	Weather(string filePath);
	~Weather();

	float getWeatherTemperature();
	int getWeatherPOP();
	float getWeatherPrecipitationAmount();
	float getWeatherWindSpeed();
	int getWeatherHumidity();
	WeatherDescription getWeatherDescription();

	void setWeatherTemperature(float temperature);
	void setWeatherPOP(int pop);
	void setWeatherPrecipitationAmount(float precipitationAmount);
	void setWeatherWindSpeed(float windSpeed);
	void setWeatherHumidity(int humidity);
	void setWeatherDescription(WeatherDescription weatherDescription);

	void displayWeather();
	void getWeatherFromFile(string filePath);


public:

	bool safeToFly;

	bool getWeatherSafety();
	void setWeatherSafety(bool safeToFly);

	void checkWeatherSafety();

};