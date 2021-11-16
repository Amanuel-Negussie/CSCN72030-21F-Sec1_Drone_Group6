#pragma once

#include <string>

using namespace std;

class Alert {

public:

	int alertCode;
	string alertMessage;

	Alert(int alertCode);


	int getAlertCode();
	string getAlertMessage();
	
	void displayAlert();
	string readAlertMessage(int alertCode);
	void getAlertLog();

};
