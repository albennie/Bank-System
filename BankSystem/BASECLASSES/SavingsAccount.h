#pragma once
#include <chrono>
#include "BankAccount.h"

class SavingsAccount : public BankAccount
{
    double interestRate = 0.5;
    std::chrono::system_clock::time_point lastInterestTime;

public:
    SavingsAccount(const std::string& cardNumber,
        const std::string& ibanNumber,
        const std::string& accountNumber,
        const std::string& cvv2,
        const std::string& expirationYear,
        const std::string& expirationMonth,
        const std::string& pin,
        const std::string& staticSecondPassword,
        long long accountBalance)
        : BankAccount(cardNumber,
            ibanNumber,
            accountNumber,
            cvv2,
            expirationYear,
            expirationMonth,
            pin,
            staticSecondPassword,
            accountBalance)
    {
        lastInterestTime = std::chrono::system_clock::now();
    }

    void applyInterest() {
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - lastInterestTime;
        if (elapsed_seconds.count() < 60) {
            return;
		}
        int minutes = static_cast<int>(elapsed_seconds.count() / 60);
        double interest = 1;

        for (int i = 0; i < minutes; ++i) {
            interest *= (1 + interestRate);
		}
        setAccountBalance(getAccountBalance() * interest);
        lastInterestTime = now;
    }

    std::string AccountType() const override {
        return "Savings Account";
    }
};

