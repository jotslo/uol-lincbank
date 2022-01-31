#include <iostream>
#include "Current.h"

using namespace std;

// assign default variables upon initialisation
Current::Current(double initialDeposit, int index, bool isIsa) {
	accountNumber = index;
	balance = initialDeposit;
	accountType = "Current";

	// create new transaction for account creation
	Transaction* transaction = new Transaction(
		"Account Creation",
		initialDeposit
	);

	// add transaction to history vector
	history.push_back(transaction);
}

// withdraw specified amount from current account
bool Current::withdraw(double amount, bool isTransfer) {
	double newBalance = balance - amount;

	// if new balance goes below overdraft, return error
	if (newBalance < -overdraft) {
		cout << "You cannot withdraw more than your overdraft allows." << endl;
		return false;
	}

	// if specified amount is positive, create new transaction
	if (amount > 0) {
		balance = newBalance;
		Transaction* transaction = new Transaction(
			isTransfer ? "Transfer" : "Withdrawal",
			-amount
		);

		// add transaction to history vector & return success
		history.push_back(transaction);
		return true;
	}

	// otherwise, return error
	cout << "The withdrawal amount must be greater than 0" << endl;
	return false;
}

// deposit specified amount into current account
bool Current::deposit(double amount, bool isTransfer) {
	// if specified amount is positive, create a new transaction
	if (amount > 0) {
		balance = balance + amount;
		Transaction* transaction = new Transaction(
			isTransfer ? "Transfer" : "Deposit",
			amount
		);

		// add transaction to history vector & return success
		history.push_back(transaction);
		return true;
	}

	// otherwise, return error
	cout << "The deposit must be greater than 0" << endl;
	return false;
}

// check whether user can open account
bool Current::canOpenAccount(vector <Account*> accounts) {
	// for each account, error if any are a current account
	for (Account*& account : accounts) {
		if (account->getAccountType() == "Current") {
			cout << "You can only have one current account." << endl;
			return false;
		}
	}
	
	// otherwise, allow account to be opened
	return true;
}

double Current::projectBalance(int years) {
	return balance;
}