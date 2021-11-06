using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <fstream>;
#include <exception>
#include <ctime>
#define CIRCUIT_FILE "./connections.txt"
#define ERROR_LOG "./ErrorLog.txt"
bool logError(string msg);
class connection {
public :
	
	char* point1;
	char* point2;
	bool testConnection(int volts);
	connection(char p1[],char p2[]);
	
private:
	int getVoltage();
};


struct noErrorLog : public exception {
	const char* issue() const throw() {
		return "Error Log Not Opened";
	}
};
