#pragma once
#include "BankAccount.h"

class CheckingAccount : public BankAccount
{
    double overdraftLimit = 500000;
    double overdraftUsed = 0.0;

public:
    CheckingAccount(const std::string& cardNumber,
                    const std::string& ibanNumber,
                    const std::string& accountNumber,
                    const std::string& cvv2,
                    const std::string& expirationYear,
                    const std::string& expirationMonth,
                    const std::string& pin,
                    const std::string& staticSecondPassword,
                    long long accountBalance)
        : BankAccount(cardNumber, ibanNumber, accountNumber, cvv2, expirationYear,
                      expirationMonth, pin, staticSecondPassword, accountBalance) {}

    bool withdraw(double amount) override {
        double available = getAccountBalance() + (overdraftLimit - overdraftUsed);

        if (amount <= available) {
            double balance = getAccountBalance();

            if (amount <= balance) {
                setAccountBalance(balance - amount);
            } else {
                double fromOverdraft = amount - balance;
                setAccountBalance(0);
                overdraftUsed += fromOverdraft;
            }

            return true;
        }

        return false;
    }

    void deposit(double amount) override {
        if (overdraftUsed > 0) {
            double repay = std::min(amount, overdraftUsed);
            overdraftUsed -= repay;
            amount -= repay;
        }

        setAccountBalance(getAccountBalance() + amount);
    }

    std::string AccountType() const override {
        return "Checking Account";
    }

    double getOverdraftUsed() const {
        return overdraftUsed;
    }

    double getRemainingOverdraft() const {
        return overdraftLimit - overdraftUsed;
    }
};
