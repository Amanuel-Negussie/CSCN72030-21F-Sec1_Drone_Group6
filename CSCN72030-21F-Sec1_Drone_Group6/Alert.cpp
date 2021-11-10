#include "Alert.h";
#include <iostream>
#include <fstream>

using namespace std;

Alert::Alert(int alertCode) {
	
	this->alertCode;
	this->alertMessage = readAlertMessage(alertCode);
}

int Alert::getAlertCode() {
	return this->alertCode;
}

string Alert::getAlertMessage() {
	return this->alertMessage;
}

void Alert::displayAlert() {
	cout << "Alert!\n\n" <<
		"AlertCode: " << this->alertCode <<
		"\n" << this->alertMessage;
}

string Alert::readAlertMessage(int alertCode) {
	return "AlertStub! readAlertMessage();";
}

void Alert::getAlertLog() {
	cout << "Alert Log";
}