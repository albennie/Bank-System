#pragma once
#include "User.h"
#include "LinkedList.h"
#include <memory>
#include <iostream>
#include "Costomer.h"

class Admin : public User {
public:
    Admin(const std::string& firstName, const std::string& lastName, const std::string& idNo,
        const std::string& username, const std::string& password,  int age_day, int age_month, int age_year)
        : User(firstName, lastName, idNo, username, password, age_day, age_month, age_year) {
    }

    void listAllCustomers(const LinkedList<std::shared_ptr<Customer>>& customers) const {
        for (int i = 0; i < customers.GetSize(); ++i) {
            auto c = customers[i];
            std::cout << i + 1 << ". " << c->getFirstName() << " " << c->getLastName()
                << " - " << c->getUsername() << "\n";
        }
    }

    bool addAccountToCustomer(std::shared_ptr<Customer> c, std::shared_ptr<BankAccount> acc) {
        return c->addAccount(acc);
    }

    bool deleteCustomer(LinkedList<std::shared_ptr<Customer>>& customers, const std::string& id) {
        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getIdNo() == id) {
                customers.Remove(customers[i]);
                return true;
            }
        }
        return false;
    }

    void editUserInfo(std::shared_ptr<User> u, const std::string& newLastName) {
        u->setLastName(newLastName);
    }
};
