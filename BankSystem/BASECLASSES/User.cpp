#include "User.h"

User::User(const std::string& firstName, const std::string& lastName, const std::string& idNo,
    const std::string& username, const std::string& password,  int age_day, int age_month, int age_year)
    : firstName(firstName), lastName(lastName), idNo(idNo),
    username(username), password(password), age_day(age_day), age_month(age_month), age_year(age_year) {
}

const std::string& User::getFirstName() const {
    return firstName;
}

const std::string& User::getLastName() const {
    return lastName;
}

const std::string& User::getIdNo() const {
    return idNo;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}


// Setters
void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void User::setIdNo(const std::string& idNo) {
    this->idNo = idNo;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}
