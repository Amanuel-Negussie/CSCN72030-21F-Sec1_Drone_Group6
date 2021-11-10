/*
* File : connection.h
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.1
* 
* UPDATE HISTORY - 
* 1.0 - Base functionality added including ( class connection, logError, getVoltage, testConnection, Exceptions : fileNotOpened, noErrorLog, wrongVoltage. { Date : November 6, 2021 } - Version created by Danny Smith	
* 1.1 - Exception renameFail added { Date : November 6, 2021 } - Updated by Danny Smith
*/

using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <fstream>;
#include <exception>
#include <ctime>
#define CIRCUIT_FILE "./batteryWaterFiles//connections.txt"
#define ERROR_LOG "./batteryWaterFiles//ErrorLog.txt"
#define TEMP_FILE "./batteryWaterFiles//temp.txt"
#define STARTUP_FILE "./batteryWaterFiles//StartupData.txt"
#define RULES_FILE "./batteryWayerFiles//Rules.txt"


// public helper classes written here since its the bottom reference
bool logError(string msg); // logs an error in a error log file with current date and time

// class connection
class connection {
public :
	
	char* point1; // one analog point
	char* point2;// two analog point
	bool testConnection(int volts); // Simulates testing a connection point with x volts
	connection(char p1[],char p2[]); // initializer holds two analog output points such as (A0,A22)
	
private:
	int getVoltage(); // get voltage from connection tests using an ASCII file
};



// Exceptions
struct fileNotOpened : public exception {
	
	const char* issue() const throw() {
		return "Error Opening File";
	}
};

struct noErrorLog : public exception {
	const char* issue() const throw() {
		return "Error Log Not Opened";
	}
};

struct wrongVoltage : public exception {
	const char* issue() const throw() {
		return "badVoltage";
	}
};
struct renameFail : public exception {
	const char* issue() const throw() {
		return "failed Rename";
	}
};


//class MyException : public std::exception {
//	const char* file;
//	int line;
//	const char* func;
//	const char* info;
//
//public:
//	MyException(const char* msg, const char* file_, int line_, const char* func_, const char* info_ = "") : std::exception(msg),
//		file(file_),
//		line(line_),
//		func(func_),
//		info(info_)
//	{
//	}
//
//	const char* get_file() const { return file; }
//	int get_line() const { return line; }
//	const char* get_func() const { return func; }
//	const char* get_info() const { return info; }
//
//};
