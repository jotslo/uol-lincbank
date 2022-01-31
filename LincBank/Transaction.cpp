#pragma warning(disable: 4996)

#include "Transaction.h"
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>

// assign default variables upon initialisation
Transaction::Transaction(string newDesc, double newValue) {
	auto chronoTime = chrono::system_clock::now();
	desc = newDesc;
	value = newValue;
	timestamp = chrono::system_clock::to_time_t(chronoTime);
	datetime = ctime(&timestamp);
}

// return description (encapsulation)
string Transaction::getDesc() {
	return desc;
}

// return value rounded down to 2 d.p (encapsulation)
double Transaction::getValue() {
	return floor(value * 100) / 100;
}

// return current date & time (encapsulation)
string Transaction::getDatetime() {
	return datetime;
}

// return transaction data in string format
string Transaction::toString() {
	return desc + " | "
		+ char(156) + to_string(getValue())
		+ " | " + datetime;
}