#pragma once
#include <string>
#include <vector>
#include "Account.h"

using namespace std;

class Data
{
public:
	string options = "\n---- Options Menu\n"
		"open [type] [initial_deposit]\n"
		"- Open an account of specified type\n"
		"- 1: Current\n"
		"- 2 : Savings\n"
		"- 3 : ISA\n"
		"- Ex : 'open 3 1000'\n\n"

		"view (index)\n"
		"- View balance and transactions\n"
		"- Displays data for all accounts if index isn't specified\n\n"

		"withdraw [index] [sum]\n"
		"- Withdraw funds from specified account\n\n"

		"deposit [index] [sum]\n"
		"- Deposit funds from specified account\n\n"

		"transfer [src] [dest] [sum]\n"
		"- Transfer funds between two specified accounts\n\n"

		"project [index] [years]\n"
		"- View projected balance of specified savings account\n\n"

		"search [value]\n"
		"- Search for a transaction made by the amount deposited/withdrawn\n\n"

		"options\n"
		"- View available options\n\n"

		"exit\n"
		"- Exit the program\n\n"

		"----Keys\n"
		"[] - Required\n"
		"() - Optional\n";

	bool isNumber(string number, bool isDouble);
	bool validateOpen(vector <string> parameters);
	bool validateView(vector <string> parameters, vector <Account*> accounts);
	bool validateWD(vector <string> parameters, vector <Account*> accounts);
	bool validateTransfer(vector <string> parameters, vector <Account*> accounts);
	bool validateProject(vector <string> parameters, vector <Account*> accounts);
	bool validateSearch(vector <string> parameters);
};

