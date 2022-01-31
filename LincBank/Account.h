#pragma once
#include <vector>
#include <string>
#include "Transaction.h"

using namespace std;

class Account
{
public:
	//Account(double initialDeposit);
	string toString();
	string getAccountType();
	virtual bool withdraw(double amount, bool isTransfer) = 0;
	virtual bool deposit(double amount, bool isTransfer) = 0;
	virtual bool canOpenAccount(vector <Account*> accounts) = 0;
	virtual double projectBalance(int years) = 0;
	bool hasOverdraft();
	double getBalance();
	double getRoundedValue(double value);
	string getAccountData();
	vector<Transaction*> getHistory();
	vector<Transaction*> getMatchingTransactions(double value);
protected:
	string accountType;
	double balance = 0;
	int interestCount = 12;
	int accountNumber = 0;
	vector<Transaction*> history;
};

