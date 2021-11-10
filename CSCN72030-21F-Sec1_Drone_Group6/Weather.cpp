

#include "Weather.h";
#include <iostream>
#include <fstream>

using namespace std;

Weather::Weather(string filePath) {

	this->temperature = 1;
	this->precipitationAmount = 50.25f;
	this->windSpeed = 22.67f;
	this->pop = 30;
	this->humidity = 68;
	this->weatherDescription = WeatherDescription::Overcast;


	this->getWeatherFromFile(filePath);
	

}


float Weather::getWeatherTemperature() {
	return this->temperature;
}

int Weather::getWeatherPOP() {
	return this->pop;
}

float Weather::getWeatherPrecipitationAmount() {
	return this->precipitationAmount;
}

float Weather::getWeatherWindSpeed() {
	return this->windSpeed;
}

int Weather::getWeatherHumidity() {
	return this->humidity;
}

WeatherDescription Weather::getWeatherDescription() {
	return this->weatherDescription;
}

bool Weather::getWeatherSafety() {
	return this->safeToFly;
}


void Weather::setWeatherTemperature(float temperature) {
	this->temperature = temperature;
}

void Weather::setWeatherPOP(int pop) {
	this->pop = pop;
}

void Weather::setWeatherPrecipitationAmount(float precipitationAmount) {
	this->precipitationAmount = precipitationAmount;
}

void Weather::setWeatherWindSpeed(float windSpeed) {
	this->windSpeed = windSpeed;
}

void Weather::setWeatherHumidity(int humidity) {
	this->humidity = humidity;
}

void Weather::setWeatherDescription(WeatherDescription weatherDescription) {
	this->weatherDescription = weatherDescription;
}

void Weather::setWeatherSafety(bool safeToFly) {
	this->safeToFly = safeToFly;
}



void Weather::displayWeather() {
	cout << "Weather: " << this->weatherDescription;
}

void Weather::getWeatherFromFile(string filePath) {
	return;
}