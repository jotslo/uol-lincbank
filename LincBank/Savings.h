#pragma once
#include "Account.h"
#include "InterestEarning.h"
class Savings :
    public Account,
    public InterestEarning
{
public:
    Savings(double initialDeposit, int index, bool isIsa);
    virtual bool withdraw(double amount, bool isTransfer);
    virtual bool deposit(double amount, bool isTransfer);
    virtual bool canOpenAccount(vector <Account*> accounts);
    virtual double computeInterest(int years);
    virtual double projectBalance(int years);
 protected:
    double interestRate = 1;
    double isa;
};

