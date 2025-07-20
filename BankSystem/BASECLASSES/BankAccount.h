#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

class BankAccount
{
private:
    std::vector<std::pair<std::chrono::system_clock::time_point, long long>> transferHistory;
public:
    void logTransfer(long long amount);
    long long transferredLast24Hours() const;

private:
    std::string CardNumber;
    std::string IBANnumber;
    std::string AccountNumber;
    std::string CVV2;
    std::string ExpirationYear;
    std::string ExpirationMonth;
    std::string PIN;
    std::string StaticSecondPassword;
    long long AccountBalance;
    std::string DynamicSecondPassword;
public:
    BankAccount() = default;
    BankAccount(const std::string& cardNumber,
        const std::string& ibanNumber,
        const std::string& accountNumber,
        const std::string& cvv2,
        const std::string& expirationDay,
        const std::string& expirationMonth,
        const std::string& pin,
        const std::string& staticSecondPassword,
        long long accountBalance);

    const std::string& getCardNumber() const;
    const std::string& getIBANnumber() const;
    const std::string& getAccountNumber() const;
    const std::string& getCVV2() const;
    long long getAccountBalance() const;
    const std::string& getExpirationYear() const;
    const std::string& getExpirationMonth() const;
    const std::string& getPIN() const;
    const std::string& getStaticSecondPassword() const;
    const std::string& getDynamicSecondPassword() const;

    void setCardNumber(const std::string& cardNumber);
    void setIBANnumber(const std::string& ibanNumber);
    void setAccountNumber(const std::string& accountNumber);
    void setCVV2(const std::string& cvv2);
    void setAccountBalance(long long accountBalance);
    void setExpirationYear(const std::string& expirationYear);
    void setExpirationMonth(const std::string& expirationMonth);
    void setPIN(const std::string& pin);
    void setStaticSecondPassword(const std::string& staticSecondPassword);
    void setDynamicSecondPassword(const std::string& dynamicSecondPassword){
        DynamicSecondPassword = dynamicSecondPassword;
    }



    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual std::string AccountType() const = 0;

};
