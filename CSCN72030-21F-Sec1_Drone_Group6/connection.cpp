#include "connection.h";



bool connection::testConnection(int volts) {
	
	return true;
}

connection::connection(char p1[],char p2[]) {
	this->point1 = p1;
	this->point2 =p2;
}

int connection::getVoltage() {
	int voltage = 0;
	ifstream file(CIRCUIT_FILE);
	if (!file.is_open()) {

	}

	return 0;
}

bool logError(string msg) {
	

	fstream file;
	file.open(ERROR_LOG, ios::app);
	if (!file.is_open()) {
		throw noErrorLog();
	}
	else {
		// current date/time based on current system
		time_t now = time(0);
		tm* ltm = localtime(&now);
		file << 1900 + ltm->tm_year <<":" << 1 + ltm->tm_mon <<":" << ltm->tm_mday << "  "<< ltm->tm_hour <<":"<< ltm->tm_min <<":"<< ltm->tm_sec << " - ERROR : " << msg <<"\n";
	}
}





