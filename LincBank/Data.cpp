#include "Data.h"
#include "Account.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// check if provided string is a number
bool Data::isNumber(string number, bool isDouble) {
	for (char& character : number) {

		// if any character is not a digit or "." (if double), return false
		if (!(isdigit(character) || (character == '.' && isDouble))) {
			return false;
		}

		// if character is ".", set isDouble var to false to prevent more than one use
		if (character == '.') {
			isDouble = false;
		}
	}

	// otherwise, string is a number and can be casted successfully
	return true;
}

// validate the open account function
bool Data::validateOpen(vector <string> parameters) {
	// if there aren't 3 arguments, return error
	if (parameters.size() != 3) {
		cout << "Incorrect format. Refer to the options menu." << endl;
 		return false;
	}

	// if deposit amount isn't a number, return error
	if (!isNumber(parameters[2], true)) {
		cout << "The deposit must be a number." << endl;
		return false;
	}

	char type = parameters[1].front();

	// if account type isn't 1-3, return error
	if (type != '1' && type != '2' && type != '3') {
		cout << "The account type must be a number from 1 to 3." << endl;
		return false;
	}
	
	// otherwise, return true
	return true;
}

// validate the view account function
bool Data::validateView(vector <string> parameters, vector <Account*> accounts) {
	// if there are 2 arguments, validate for view [index]
	if (parameters.size() == 2) {
		string index = parameters[1];

		// if index isn't a number, return error
		if (!isNumber(index, false)) {
			cout << "The provided index must be a number." << endl;
			return false;
		}

		// if index is not a valid account number, return error
		if (accounts.size() < stoi(index) || index == "0") {
			cout << "That account number does not exist." << endl;
			return false;
		}
	}

	// if there are more than 2 arguments, format isn't correct, return error
	else if (parameters.size() > 2) {
		cout << "Incorrect format. Refer to the options menu." << endl;
		return false;
	}

	// otherwise, user wants to view all accounts, no extra validation needed
	return true;
}

// validate withdrawal and deposit functions
bool Data::validateWD(vector <string> parameters, vector <Account*> accounts) {
	// if there aren't at least 3 arguments, return error
	if (parameters.size() < 3) {
		cout << "Incorrect format. Refer to the options menu." << endl;
		return false;
	}

	// if amount specified isn't a number, return error
	if (!isNumber(parameters[2], true)) {
		cout << "The amount specified must be a number." << endl;
		return false;
	}

	string index = parameters[1];

	// if account number isn't a number, return error
	if (!isNumber(index, false)) {
		cout << "The provided index must be a number." << endl;
		return false;
	}

	// if account number isn't valid, return error
	if (accounts.size() < stoi(index) || index == "0") {
		cout << "That account number does not exist." << endl;
		return false;
	}

	// otherwise, allow transaction to take place
	return true;
}

// validate transfer function
bool Data::validateTransfer(vector <string> parameters, vector <Account*> accounts) {
	// if there aren't 4 arguments, return error
	if (parameters.size() != 4) {
		cout << "Incorrect format. Refer to the options menu." << endl;
		return false;
	}

	// if the transfer amount isn't a number, return error
	if (!isNumber(parameters[3], true)) {
		cout << "The amount specified must be a number." << endl;
		return false;
	}

	string source = parameters[1];
	string destination = parameters[2];

	// if source or destination account numbers aren't numbers, return error
	if (!isNumber(source, false) || !isNumber(destination, false)) {
		cout << "The provided indexes must be numbers." << endl;
		return false;
	}

	// if source or destination account numbers aren't valid, return error
	if (accounts.size() < stoi(source) || source == "0" || accounts.size() < stoi(destination) || destination == "0") {
		cout << "One or more of the account numbers do not exist." << endl;
		return false;
	}

	// otherwise, allow transfer to take place
	return true;
}

// validate interest projection function
bool Data::validateProject(vector <string> parameters, vector <Account*> accounts) {
	// if there aren't 3 arguments, return error
	if (parameters.size() != 3) {
		cout << "Incorrect format. Refer to the options menu." << endl;
		return false;
	}

	string index = parameters[1];
	
	// if specified index isn't a number, return error
	if (!isNumber(index, false)) {
		cout << "The provided index must be a number." << endl;
		return false;
	}

	int intIndex = stoi(index);

	// if account number is invaild, return error
	if (accounts.size() < intIndex || index == "0") {
		cout << "That account number does not exist." << endl;
		return false;
	}

	// if year is invalid, return error
	if (!isNumber(parameters[2], false)) {
		cout << "The provided year must be an integer." << endl;
		return false;
	}

	string type = accounts[intIndex - 1]->getAccountType();

	// if account type is not savings account, return error
	if (type == "Current") {
		cout << "You can only project savings accounts." << endl;
		return false;
	}

	// otherwise allow projection
	return true;
}

// validate search function
bool Data::validateSearch(vector <string> parameters) {
	// if there aren't 2 arguments, return error
	if (parameters.size() != 2) {
		cout << "Incorrect format. Refer to the options menu." << endl;
		return false;
	}

	string number = parameters[1];

	// if number is negative, remove minus for error checking
	if (number.front() == '-') {
		number.erase(0, 1);
	}

	// if specified amount isn't a number, return error
	if (!isNumber(number, true)) {
		cout << "The amount specified must be a number." << endl;
		return false;
	}

	// otherwise, allow search
	return true;
}