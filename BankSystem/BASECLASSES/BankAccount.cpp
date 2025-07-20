#include "BankAccount.h"

BankAccount::BankAccount(const std::string& cardNumber,
    const std::string& ibanNumber,
    const std::string& accountNumber,
    const std::string& cvv2,
    const std::string& expirationYear,
    const std::string& expirationMonth,
    const std::string& pin,
    const std::string& staticSecondPassword,
    long long accountBalance)
    : CardNumber(cardNumber),
    IBANnumber(ibanNumber),
    AccountNumber(accountNumber),
    CVV2(cvv2),
    ExpirationYear(expirationYear),
    ExpirationMonth(expirationMonth),
    PIN(pin),
    StaticSecondPassword(staticSecondPassword),
    AccountBalance(accountBalance)
{}

const std::string& BankAccount::getCardNumber() const {
    return CardNumber;
}

const std::string& BankAccount::getIBANnumber() const {
    return IBANnumber;
}

const std::string& BankAccount::getAccountNumber() const {
    return AccountNumber;
}

const std::string& BankAccount::getCVV2() const {
    return CVV2;
}

long long BankAccount::getAccountBalance() const {
    return AccountBalance;
}

const std::string& BankAccount::getExpirationYear() const {
    return ExpirationYear;
}

const std::string& BankAccount::getExpirationMonth() const {
    return ExpirationMonth;
}

const std::string& BankAccount::getPIN() const {
    return PIN;
}

const std::string& BankAccount::getStaticSecondPassword() const {
    return StaticSecondPassword;
}

const std::string& BankAccount::getDynamicSecondPassword() const {
    return DynamicSecondPassword;
}



void BankAccount::setCardNumber(const std::string& cardNumber) {
    CardNumber = cardNumber;
}

void BankAccount::setIBANnumber(const std::string& ibanNumber) {
    IBANnumber = ibanNumber;
}

void BankAccount::setAccountNumber(const std::string& accountNumber) {
    AccountNumber = accountNumber;
}

void BankAccount::setCVV2(const std::string& cvv2) {
    CVV2 = cvv2;
}

void BankAccount::setAccountBalance(long long accountBalance) {
    AccountBalance = accountBalance;
}

void BankAccount::setExpirationYear(const std::string& expirationDay) {
    ExpirationYear = expirationDay;
}

void BankAccount::setExpirationMonth(const std::string& expirationMonth) {
    ExpirationMonth = expirationMonth;
}

void BankAccount::setPIN(const std::string& pin) {
    PIN = pin;
}

void BankAccount::setStaticSecondPassword(const std::string& staticSecondPassword) {
    StaticSecondPassword = staticSecondPassword;
}


void BankAccount::deposit(double amount) {
    setAccountBalance(getAccountBalance() + amount);
}

bool BankAccount::withdraw(double amount) {
    if (getAccountBalance() >= amount) {
        setAccountBalance(getAccountBalance() - amount);
        return true;
    }
    return false;
}
void BankAccount::logTransfer(long long amount) {
    auto now = std::chrono::system_clock::now();
    transferHistory.push_back({now, amount});
}

long long BankAccount::transferredLast24Hours() const {
    auto now = std::chrono::system_clock::now();
    long long sum = 0;

    for (const auto& [time, amount] : transferHistory) {
        auto duration = std::chrono::duration_cast<std::chrono::hours>(now - time);
        if (duration.count() < 24) {
            sum += amount;
        }
    }

    return sum;
}
