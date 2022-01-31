#pragma once

#include "Account.h"

class Current :
    public Account
{
public:
    Current(double initialDeposit, int index, bool isIsa);
    virtual bool withdraw(double amount, bool isTransfer);
    virtual bool deposit(double amount, bool isTransfer);
    virtual bool canOpenAccount(vector <Account*> accounts);
    virtual double projectBalance(int years);
protected:
    double overdraft = 500;
    int accountTotal = 0;
};