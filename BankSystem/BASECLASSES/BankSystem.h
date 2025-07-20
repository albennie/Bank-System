#pragma once
#include "Admin.h"
#include "LinkedList.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <BASECLASSES/Qarz_al_HasanAccount.h>
#include <BASECLASSES/CheckingAccount.h>
#include <BASECLASSES/SavingsAccount.h>

class BankSystem {
private:
    LinkedList<std::shared_ptr<Customer>> customers;
    LinkedList<std::shared_ptr<Admin>> admins;
    std::shared_ptr<User> currentUser;

public:
    BankSystem() {
        srand(time(nullptr));

        auto acc50 = std::make_shared<CheckingAccount>("6104411445282484", "IR567823125093747410502837", "9277475062251", "5286", "02", "06", "7194", "994012", 8855662);
        auto acc51 = std::make_shared<CheckingAccount>("6104317526799528", "IR472952234967947793191307", "2507319895238", "3043", "23", "12", "6000", "918821", 5542917);
        auto acc52 = std::make_shared<Qarz_al_HasanAccount>("6104258987397981", "IR707443119244356369372190", "8271933954607", "6719", "11", "11", "3770", "469138", 2123062);


        admins.AddFront(std::make_shared<Admin>("Benjamin","Sheikh","2111199192","admin","123456",20,12,1363));
        admins.AddFront(std::make_shared<Admin>("Kousar","Sheikh","2111199193","admin2","123456",18,12,1363));

        auto acc00 = std::make_shared<CheckingAccount>("6104094171377646", "IR171063936541985713837073", "7221444778291", "5756", "06", "01", "6723", "262454", 6676449);
        auto acc01 = std::make_shared<SavingsAccount>("6104178585278716", "IR954207002970077880621029", "8954359681095", "4789", "05", "08", "2476", "674039", 3890336);
        auto user1 = std::make_shared<Customer>("Ali", "Mohammadi", "2111199194", "user1", "1", 11,12,1363);
        user1->addAccount(acc00);
        user1->addAccount(acc01);
        user1->addAccount(acc51);

        auto acc10 = std::make_shared<CheckingAccount>("6104761812363469", "IR198356396981410483403887", "7810805865744", "3109", "14", "04", "8783", "533960", 5158523);
        auto acc11 = std::make_shared<SavingsAccount>("6104143594914716", "IR755171576308580201576917", "8188227157442", "2623", "06", "05", "7250", "511661", 7161639);
        auto acc12 = std::make_shared<Qarz_al_HasanAccount>("6104360150707912", "IR134538483810578741965431", "3523725790855", "7937", "06", "02", "6411", "513953", 4111123);
        auto user2 = std::make_shared<Customer>("Sara", "Karimi", "2111199195", "user2", "2", 5,12,1363);
        user2->addAccount(acc10);
        user2->addAccount(acc11);
        user2->addAccount(acc12);
        user2->addAccount(acc50);

        auto acc20 = std::make_shared<CheckingAccount>("6104220335681568", "IR895227235993589362877055", "8535804907015", "4692", "09", "02", "1847", "476418", 4745990);
        auto acc21 = std::make_shared<SavingsAccount>("6104951542751348", "IR478308505339594310052476", "6999838373902", "7612", "21", "11", "4727", "960052", 5756926);
        auto user3 = std::make_shared<Customer>("Reza", "Naseri", "2111199196", "user3", "3", 29,12,1363);
        user3->addAccount(acc20);
        user3->addAccount(acc21);
        user3->addAccount(acc52);

        auto acc30 = std::make_shared<CheckingAccount>("6104387955563609", "IR440521381996644594360718", "3679151238258", "5569", "15", "02", "1200", "957113", 3714464);
        auto acc31 = std::make_shared<SavingsAccount>("6104617901380629", "IR602369900452170307349867", "2906665241051", "3099", "05", "01", "2430", "662402", 8816480);
        auto acc32 = std::make_shared<Qarz_al_HasanAccount>("6104304866657271", "IR213873797884557332272109", "7873335808878", "0025", "09", "07", "8106", "486908", 6329005);
        auto user4 = std::make_shared<Customer>("Zahra", "Ebrahimi", "2111199197", "user4", "4", 22,12,1363);
        user4->addAccount(acc30);
        user4->addAccount(acc31);
        user4->addAccount(acc32);

        auto acc40 = std::make_shared<SavingsAccount>("6104643580884075", "IR899977272677766502888218", "1353672274322", "3390", "15", "05", "1703", "982890", 7370314);
        auto acc41 = std::make_shared<Qarz_al_HasanAccount>("6104845359743205", "IR658832539259378424973876", "5524331414210", "9932", "08", "10", "1142", "518282", 4679033);
        auto user5 = std::make_shared<Customer>("Mohammad", "Shirazi", "2111199198", "user5", "5", 28,12,1363);
        user5->addAccount(acc40);
        user5->addAccount(acc41);

        customers.PushBack(user1);
        customers.PushBack(user2);
        customers.PushBack(user3);
        customers.PushBack(user4);
        customers.PushBack(user5);

    }

    bool removeCustomerById(const std::string& id) {
        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getIdNo() == id) {
                customers.Remove(customers[i]);
                return true;
            }
        }
        return false;
    }

    bool login(const std::string& uname, const std::string& pass) {
        for (int i = 0; i < admins.GetSize(); ++i) {
            if (admins[i]->getUsername() == uname && admins[i]->getPassword() == pass) {
                currentUser = admins[i];
                return true;
            }
        }

        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getUsername() == uname && customers[i]->getPassword() == pass) {
                currentUser = customers[i];
                return true;
            }
        }

        return false;
    }

    void logout() {
        currentUser = nullptr;
    }

    std::shared_ptr<User> getCurrentUser() const {
        return currentUser;
    }

    shared_ptr<Customer> getCurrentCustomer() const
    {
        return std::dynamic_pointer_cast<Customer>(currentUser);
    }




    std::shared_ptr<Customer> getCustomerByCard(const std::string& cardNumber) {
        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->findAccountByCard(cardNumber)) {
                return customers[i];
            }
        }
        return nullptr;
    }

    bool addCustomer(string f,string l,string id,string u,string p,int d,int m,int y){
        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getUsername() == u) return false;
        }
        for (int i = 0; i < admins.GetSize(); ++i) {
            if (admins[i]->getUsername() == u) return false;
        }

        customers.PushBack(std::make_shared<Customer>(f,l,id,u,p,d,m,y));
        return true;
    }

    bool addAdmin(string f,string l,string id,string u,string p,int d,int m,int y){
        for (int i = 0; i < admins.GetSize(); ++i) {
            if (admins[i]->getUsername() == u) return false;
        }

        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getUsername() == u) return false;
        }

        admins.PushBack(std::make_shared<Admin>(f,l,id,u,p,d,m,y));
        return true;
    }

    LinkedList<std::shared_ptr<Customer>>& getCustomers() {
        return customers;
    }

    LinkedList<std::shared_ptr<Admin>>& getAdmins() {
        return admins;
    }

    bool isAdminLoggedIn() const {
        return std::dynamic_pointer_cast<Admin>(currentUser) != nullptr;
    }

    bool isCustomerLoggedIn() const {
        return std::dynamic_pointer_cast<Customer>(currentUser) != nullptr;
    }
};
