#define _CRT_SECURE_NO_WARNINGS
#include "Alert.h";
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>


using namespace std;

Alert::Alert(int alertCode) {
	this->alertCode = alertCode;
	this->alertMessage = readAlertMessage(alertCode);
	displayAlert();
	updateAlertLog(this);
}

int Alert::getAlertCode() {
	return this->alertCode;
}

string Alert::getAlertMessage() {
	return this->alertMessage;
}

void Alert::displayAlert() {
	cout << "Alert!\n------\n" <<
		"AlertCode: " << this->alertCode <<
		"\nAlertMessage: " << this->alertMessage << "\n\n";
}

string Alert::readAlertMessage(int alertCode) {
	
	const string alertDirectory = "Alerts/";
	const string fileDirectory = alertDirectory + to_string(alertCode) + ".txt";
	
	ifstream file(fileDirectory);
	if (!file.is_open()) {
		return "Error, could not find alert message.\n";
	}

	string alertMessage((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	file.close();

	return alertMessage;
	
}

void Alert::updateAlertLog(Alert* a) {

	const string alertLogDirectory = "Alerts/alertLog.txt";
	ofstream file(alertLogDirectory, ios_base::app);
	if (!file.is_open()) {
		cout << "Error, could not find alert log." << endl;
	}

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();
	time_t end_time = std::chrono::system_clock::to_time_t(end);

	file << "Alert: " << ctime(&end_time) << 
		"-------------------------------\n";
	file << "Alert Code:\t" + to_string(a->alertCode) + "\n";
	file << "Message:\t" + a->alertMessage + "\n";
	file << "-------------------------------\n";
	file.close();

}

void getAlertLog() {

	const string alertLogDirectory = "Alerts/alertLog.txt";

	ifstream file(alertLogDirectory);
	if (!file.is_open()) {
		cout << "Error, could not find alert log." << endl;
	}
	cout << "Alert Log: \n-------------------------------\n";

	string alertMessage((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	file.close();

	cout << alertMessage;
}