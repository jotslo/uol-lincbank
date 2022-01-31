#pragma once
#include <string>

using namespace std;

class Transaction
{
public:
	Transaction(string newDesc, double newValue);
	string toString();
	string getDesc();
	double getValue();
	string getDatetime();
protected:
	string desc;
	time_t timestamp;
	double value;
	string datetime;
};

