#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "InterestEarning.h"
#include "Data.h"

using namespace std;

int main()
{
	Data data;
	vector <string> parameters;
	vector <Account*> accounts;
	string userCommand;

	cout << "~~~ Welcome to LincBank! ~~~\n"
		"For a list of commands, type 'options'\n"
		"Please note, these commands are CaSe SEnsItIVE!\n";

	// keep taking input until user requests to exit program
	while (userCommand != "exit")
	{
		// clear parameters vector for next command and request input
		parameters.clear();
		cout << endl << ">>> ";
		getline(cin, userCommand);

		// create c string of command length
		int cmdLength = userCommand.length();
		char* cstr = new char[cmdLength + 1];
		strcpy(cstr, userCommand.c_str());

		// in the case that no command is entered, avoid error
		// and skip to next iteration
		if (cmdLength == 0) {
			continue;
		}

		// generate token for each set of chars in string, separated by space
		char* token;
		token = strtok(cstr, " ");

		// while token exists, add to parameters vector to be referenced later
		while (token != NULL) {
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// define all commands as per the brief
		string command = parameters[0];

		// display the various commands to the user
		if (command.compare("options") == 0) {
			cout << data.options << endl;
		}

		// open account if input validation is successful
		else if (command.compare("open") == 0 && data.validateOpen(parameters)) {
			int index = accounts.size() + 1;
			char type = parameters[1].front();
			double deposit = stod(parameters[2]);
			Account* account;
			
			// if account type 1, create current account
			if (type == '1') {
				account = new Current(deposit, index, false);
			}

			// otherwise, create savings/isa account depending on type
			else {
				account = new Savings(deposit, index, type == '3');
			}

			// if account-specific validation is successful, add to accounts vector
			if (account->canOpenAccount(accounts)) {
				accounts.push_back(account);
				cout << "Account number " << to_string(index) << " created!" << endl;
			}
		}

		// view account information if validation is successful
		else if (command.compare("view") == 0 && data.validateView(parameters, accounts)) {
			vector <Account*> queriedAccounts;

			// if account number specified, add specified account to new vector
			if (parameters.size() >= 2) {
				int index = stoi(parameters[1]);
				queriedAccounts.push_back(accounts[index - 1]);
			}

			// otherwise, add all attached accounts to the vector
			else {
				queriedAccounts = accounts;
			}

			// for each specified account, output account information
			for (Account*& account : queriedAccounts) {
				cout << endl << account->toString()
					<< account->getBalance() << setprecision(2) << fixed
					<< endl << "Recent Transactions: " << endl;

				// for each transaction per account, output transaction info
				for (Transaction*& transaction : account->getHistory()) {
					cout << "- " << transaction->getDesc() << " | " << char(156)
						<< transaction->getValue() << setprecision(2) << fixed
						<< " | " << transaction->getDatetime();
				}
			}
 		}

		// withdraw amount from specified account if validation is successful
		else if (command.compare("withdraw") == 0 && data.validateWD(parameters, accounts)) {
			int index = stoi(parameters[1]);
			double amount = stod(parameters[2]);

			// call withdraw function, which performs extra account specific validation
			// use false to represent that this is not a transfer
			Account* account = accounts[index - 1];
			bool success = account->withdraw(amount, false);

			// if withdrawal successful, inform user
			if (success) {
				cout << "Successfully withdrawn from your account." << endl;
 			}
		}

		// deposit amount into specified account if validation is successful
		else if (command.compare("deposit") == 0 && data.validateWD(parameters, accounts)) {
			int index = stoi(parameters[1]);
			double amount = stod(parameters[2]);

			// call deposit function, which performs extra account specific validation
			// use false to represent that this is not a transfer
			Account* account = accounts[index - 1];
			bool success = account->deposit(amount, false);

			// if deposit successful, inform user
			if (success) {
				cout << "Successfully deposited to your account." << endl;
			}
		}

		// transfer amount between specified accounts if validation is successful
		else if (command.compare("transfer") == 0 && data.validateTransfer(parameters, accounts))
		{
			int source = stoi(parameters[1]);
			int destination = stoi(parameters[2]);
			double amount = stod(parameters[3]);

			// call withdraw function from source account, which performs extra validation
			// use true to represent that this is not a transfer
			Account* srcAccount = accounts[source - 1];
			Account* destAccount = accounts[destination - 1];
			bool success = srcAccount->withdraw(amount, true);

			// if withdrawal is successful, deposit the same amount into destination account
			if (success) {
				destAccount->deposit(amount, true);
				cout << "Successfully transferred funds between your accounts." << endl;
			}
		}

		// calculate interest projection for specified amount of years if validation is successful
		else if (command.compare("project") == 0 && data.validateProject(parameters, accounts)) {
			int index = stoi(parameters[1]);
			int years = stoi(parameters[2]);

			Account* account = accounts[index - 1];

			// call projectBalance function and then output the response
			double projection = account->projectBalance(years);
			cout << "Projected Balance: " << char(156)
				<< projection << setprecision(2) << fixed << endl;
		}

		// search for transactions with specific value if validation is successful
		else if (command.compare("search") == 0 && data.validateSearch(parameters)) {
			double amount = stod(parameters[1]);

			// for each account, get vector containing matching transactions
			for (Account*& account : accounts) {
				vector <Transaction*> results = account->getMatchingTransactions(amount);

				// for each matching transaction, output account data + transaction info
				for (Transaction*& transaction : results) {
					cout << account->getAccountData() << " | " << transaction->getDesc()
						<< " | " << char(156) << transaction->getValue() << setprecision(2)
						<< fixed << " | " << transaction->getDatetime();
				}
			}
		}
	}

	// after typing "exit", listen for next key-press before exiting
	std::cout << "Press any key to quit...";
	std::getchar();
}