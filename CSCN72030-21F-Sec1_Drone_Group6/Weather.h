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

class Weather {

	float temperature, precipitationAmount, windSpeed;
	int pop, humidity;
	WeatherDescription weatherDescription;

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


public:

	Weather(string);

	bool safeToFly;

	bool getWeatherSafety();
	void setWeatherSafety(bool safeToFly);
	void displayWeather();
	void getWeatherFromFile(string filePath);


};