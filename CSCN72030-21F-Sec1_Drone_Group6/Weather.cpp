

#include "Weather.h";
#include "batteryWater.h"
#include <iostream>
#include <fstream>

using namespace std;

Weather::Weather(string weatherFileName) {

	try {
		const string weatherDirectory = "Weather/";
		string path = weatherDirectory + weatherFileName + ".txt";
		this->getWeatherFromFile(path);
	} catch (const char* msg) {
		cout << msg << endl;
	}

}

ostream& operator << (ostream& stream, WeatherDescription weatherDescription) {
	const string weatherDescriptionString[] = { "Sunny", "Cloudy", "Overcast", "Showers", "Rainstorm", "Snow", "Custom"};

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

void Weather::createCustomWeather() {

	string str;
	this->weatherDescription = Custom;

	cout << "Please enter the Temperature: ";
	cin >> str;
	cout << endl;
	this->temperature = stof(str);

	cout << "Please enter the POP: ";
	cin >> str;
	cout << endl;
	this->pop = stoi(str);

	cout << "Please enter the Pecipitation Amount: ";
	cin >> str;
	cout << endl;
	this->precipitationAmount = stof(str);

	cout << "Please enter the Humidity Precentage: ";
	cin >> str;
	cout << endl;
	this->humidity = stoi(str);

	cout << "Please enter the Wind Speed: ";
	cin >> str;
	cout << endl;
	this->windSpeed = stof(str);

	cout << "Is it safe to fly (y, n): ";
	cin >> str;
	if (str == "y") {
		this->safeToFly = true;
	} else {
		this->safeToFly = false;
	}

	cout << endl << "Weather Updated" << endl;

	this->displayWeather();


}

void Weather::setWeatherSafety(bool safeToFly) {
	this->safeToFly = safeToFly;
}

void Weather::displayWeather() {

	try {

		if (this->weatherDescription != Sunny &&
			this->weatherDescription != Cloudy &&
			this->weatherDescription != Showers &&
			this->weatherDescription != Rainstorm &&
			this->weatherDescription != Snow &&
			this->weatherDescription != Custom &&
			this->weatherDescription != Overcast) {
			throw "weather null";
			return;
		}


		cout << "Weather: " << endl
			<< "-------" << endl
			<< "Description: " << this->weatherDescription << endl
			<< "Temperature: " << this->temperature << " Degree Celcius" << endl
			<< "POP: " << this->pop << "%" << endl
			<< "Precipitation Amount: " << this->precipitationAmount << "mm" << endl
			<< "Wind Speed: " << this->windSpeed << "km/h" << endl
			<< "Humidity: " << this->humidity << "%" << endl;

		if (this->safeToFly == true) {
			cout << "Safe To Fly: true" << endl;
		} else {
			cout << "Safe To Fly: false" << endl;
		}
	} catch (const char* msg) {
		logError("SYSTEM ERROR: Weather Object Error");
	}
		
}

void Weather::getWeatherFromFile(string filePath) {

	ifstream file(filePath);
	if (!file.is_open()) {
		//cout << "Error, could not find weather file.\n";
		throw "Could not find weather file.";
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