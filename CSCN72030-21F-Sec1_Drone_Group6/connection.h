


class connection {
public :
	
	char* point1;
	char* point2;
	bool testConnection(int volts);
	connection(char p1[],char p2[]);
private:
	int getVoltage();
};