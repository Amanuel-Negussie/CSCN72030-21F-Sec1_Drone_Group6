#define _CRT_SECURE_NO_WARNINGS
#include "Alert.h";
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "batteryWater.h"
using namespace std;

Alert::Alert(int alertCode) {
	try {
		this->alertCode = alertCode;
		this->alertMessage = readAlertMessage(alertCode);
		displayAlert();
		updateAlertLog(this);
	} catch (const char* msg) {
		cout << msg << endl;
	}
}

int Alert::getAlertCode() {
	return this->alertCode;
}

string Alert::getAlertMessage() {
	return this->alertMessage;
}

void Alert::displayAlert() {
	setCursorPosition(0, 15);
	cout << "AlertCode: " << this->alertCode <<
		"\nAlertMessage: " << this->alertMessage << "\n\n";
	Sleep(1000);
}

string Alert::readAlertMessage(int alertCode) {
	
	const string alertDirectory = "Alerts/";
	const string fileDirectory = alertDirectory + to_string(alertCode) + ".txt";
	
	ifstream file(fileDirectory);
	if (!file.is_open()) {
		//return "Error, could not find alert message.\n";
		setCursorPosition(0, 15);
		throw "Error, could not find alert message.";
	}

	string alertMessage((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	file.close();

	return alertMessage;
	
}

void Alert::updateAlertLog(Alert* a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const string alertLogDirectory = "Alerts/alertLog.txt";
	ofstream file(alertLogDirectory, ios_base::app);
	if (!file.is_open()) {
		cout << "Error, could not find alert log." << endl;
	}

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();
	time_t end_time = std::chrono::system_clock::to_time_t(end);
	SetConsoleTextAttribute(hConsole, 12);
	file << "Alert: " << ctime(&end_time) << 
		"-------------------------------\n";
	file << "Alert Code:\t" + to_string(a->alertCode) + "\n";
	file << "Message:\t" + a->alertMessage + "\n";
	file << "-------------------------------\n";
	file.close();
	SetConsoleTextAttribute(hConsole, 15);
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
