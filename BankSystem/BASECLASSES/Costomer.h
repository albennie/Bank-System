#pragma once
#include "BASECLASSES/User.h"
#include "BASECLASSES/BankAccount.h"
#include "BASECLASSES/LinkedList.h"
#include <memory>

class Customer : public User {
private:
    LinkedList<std::shared_ptr<BankAccount>> accounts;
public:
    Customer() = default;
    Customer(const std::string& firstName, const std::string& lastName, const std::string& idNo,
        const std::string& username, const std::string& password, int age_day, int age_month, int age_year)
        : User(firstName, lastName, idNo, username, password, age_day, age_month, age_year) {    }

    bool addAccount(std::shared_ptr<BankAccount> account) {
        if (accounts.GetSize() >= 5) return false;
        accounts.PushBack(account);
        return true;
    }

    bool removeAccount(const std::string& cardNumber) {
        for (int i = 0; i < accounts.GetSize(); ++i) {
            if (accounts[i]->getCardNumber() == cardNumber) {
                accounts.Remove(accounts[i]);
                return true;
            }
        }
        return false;
    }


    int getAccountNumber()
    {
        return accounts.GetSize();
    }

    std::shared_ptr<BankAccount> findAccountByCard(const std::string& card) const {
        for (int i = 0; i < accounts.GetSize(); ++i) {
            if (accounts[i]->getCardNumber() == card)
                return accounts[i];
        }
        return nullptr;
    }

    bool changePIN(const std::string& card, const std::string& newPIN) {
        auto acc = findAccountByCard(card);
        if (!acc) return false;
        acc->setPIN(newPIN);
        return true;
    }

    bool changeStaticSecondPassword(const std::string& card, const std::string& newPass) {
        auto acc = findAccountByCard(card);
        if (!acc) return false;
        acc->setStaticSecondPassword(newPass);
        return true;
    }
    const LinkedList<std::shared_ptr<BankAccount>>& getAccounts() const { return accounts; }
};
