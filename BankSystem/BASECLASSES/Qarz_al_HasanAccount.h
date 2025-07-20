#pragma once
#include "BankAccount.h"

class Qarz_al_HasanAccount : public BankAccount
{
public:
    Qarz_al_HasanAccount(const std::string& cardNumber,
                             const std::string& ibanNumber,
                             const std::string& accountNumber,
                             const std::string& cvv2,
                             const std::string& expirationYear,
                             const std::string& expirationMonth,
                             const std::string& pin,
                             const std::string& staticSecondPassword,
                             long long accountBalance):BankAccount(cardNumber,
                                   ibanNumber,
                                   accountNumber,
                                   cvv2,
                                   expirationYear,
                                   expirationMonth,
                                   pin,
                                   staticSecondPassword,
                      accountBalance) {}


    std::string AccountType() const override {
        return "Qarz_al_Hasan Account";
    }
};

