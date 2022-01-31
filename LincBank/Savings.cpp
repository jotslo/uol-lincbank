#include <iostream>
#include "Savings.h"

using namespace std;

// assign default variables upon initialisation
Savings::Savings(double initialDeposit, int index, bool isIsa) {
	balance = initialDeposit;
	accountNumber = index;

	// create new transaction for account creation
	Transaction* transaction = new Transaction(
		"Account Creation",
		initialDeposit
	);

	// set interest rate depending on account type
	if (isIsa) {
		accountType = "ISA";
		interestRate = 0.0115;
	}
	else {
		accountType = "Savings";
		interestRate = 0.0085;
	}

	// add transaction to history vector
	history.push_back(transaction);
}

// determine value after interest projection
double Savings::computeInterest(int years) {
	double projection = balance * pow(
		1 + interestRate / interestCount,
		interestCount * years
	);

	// round projection to 2 d.p, & return
	return floor(projection * 100) / 100;
}

// withdraw specified amount from savings account
bool Savings::withdraw(double amount, bool isTransfer) {
	double newBalance = balance - amount;

	// if new balance is less than 0, return error
	if (newBalance < 0) {
		cout << "You don't have enough funds to withdraw." << endl;
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
	cout << "The deposit must be greater than 0" << endl;
	return false;
}

// deposit specific amount into savings account
bool Savings::deposit(double amount, bool isTransfer) {
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

// check whether a user can open account
bool Savings::canOpenAccount(vector <Account*> accounts) {
	// if general savings account, allow
	if (accountType == "Savings") {
		return true;
	}

	// otherwise, check for existing isas and prevent if any matches
	for (Account*& account : accounts) {
		if (account->getAccountType() == "ISA") {
			cout << "You can only have one ISA account." << endl;
			return false;
		}
	}

	// if balance is less than minimum 1,000 deposit, return error
	if (balance < 1000) {
		cout << "ISA accounts must have a deposit of at least "
			<< char(156) << "1,000" << endl;
		return false;
	}
	
	// otherwise, return success
	return true;
}

double Savings::projectBalance(int years) {
	return computeInterest(years);
}