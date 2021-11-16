

#include "Weather.h";
#include <iostream>
#include <fstream>

using namespace std;

Weather::Weather(string weatherFileName) {

	const string weatherDirectory = "Weather/";
	string path = weatherDirectory + weatherFileName + ".txt";
	this->getWeatherFromFile(path);

}

ostream& operator << (ostream& stream, WeatherDescription weatherDescription) {
	const string weatherDescriptionString[] = { "Sunny", "Cloudy", "Overcast", "Showers", "Rainstorm", "Snow" };
	return stream << weatherDescriptionString[weatherDescription];
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
	cout << "Weather: " << endl
		<< "-------" << endl
		<< "Description: " << this->weatherDescription << endl
		<< "Temperature: " << this->temperature << endl
		<< "POP: " << this->pop << endl
		<< "Precipitation Amount: " << this->precipitationAmount << endl
		<< "Wind Speed: " << this->windSpeed << endl
		<< "Humidity: " << this->humidity << endl
		<< "Safe To Fly: " << this->safeToFly << endl;
}

void Weather::getWeatherFromFile(string filePath) {

	ifstream file(filePath);
	if (!file.is_open()) {
		cout << "Error, could not find weather file.\n";
		return;
	}
	
	string line;

	getline(file, line);
	this->temperature = stof(line);

	getline(file, line);
	this->pop = stoi(line);

	getline(file, line);
	this->precipitationAmount = stof(line);

	getline(file, line);
	this->windSpeed = stof(line);

	getline(file, line);
	this->humidity = stoi(line);

	getline(file, line);
	if (line == "Sunny") {
		this->weatherDescription = Sunny;
	} else if (line == "Cloudy") {
		this->weatherDescription = Cloudy;
	} else if (line == "Rainstorm") {
		this->weatherDescription = Rainstorm;
	} else if (line == "Snow") {
		this->weatherDescription = Snow;
	} else if (line == "Overcast") {
		this->weatherDescription = Overcast;
	} else if (line == "Showers") {
		this->weatherDescription = Showers;
	}

	getline(file, line);
	if (line == "true") {
		this->safeToFly = true;
	} else {
		this->safeToFly = false;
	}


	file.close();


}