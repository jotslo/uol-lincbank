#include "Account.h"
#include <string>
#include <iostream>

using namespace std;

//Account::Account(double initialDeposit) {
//	balance = initialDeposit;
//}

// return rounded balance (encapsulation)
double Account::getBalance() {
	return getRoundedValue(balance);
}

// return account type (encapsulation)
string Account::getAccountType() {
	return accountType;
}

// return formatted information about account
string Account::getAccountData() {
	return accountType + " Account " + to_string(accountNumber);
}

// return transaction history (encapsulation)
vector<Transaction*> Account::getHistory() {
	return history;
}

// return value rounded down to 2 d.p.
double Account::getRoundedValue(double value) {
	return floor(value * 100) / 100;
}

// return vector of transactions matching value
vector<Transaction*> Account::getMatchingTransactions(double value) {
	vector <Transaction*> matchingTransactions;

	// for each transaction, if value matches rounded value, add to vector
	for (Transaction*& transaction : history) {
		if (transaction->getValue() == getRoundedValue(value)) {
			matchingTransactions.push_back(transaction);
		}
	}

	// return vector containing matching transactions
	return matchingTransactions;
}

// return account information formatted as string to be outputted
string Account::toString() {
	return accountType + " Account\nBalance: "
		+ char(156);
}