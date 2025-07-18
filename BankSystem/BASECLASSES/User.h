#pragma once
#include <string>

class User {
private:
    std::string firstName;
    std::string lastName;
    std::string idNo;
    std::string username;
    std::string password;
    int age_day;
    int age_month;
    int age_year;
public:
    User() = default;
    User(const std::string& firstName, const std::string& lastName, const std::string& idNo,
        const std::string& username, const std::string& password, int age_day, int age_month, int age_year);

    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getIdNo() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    int getAgeYear() { return age_year; }


    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setIdNo(const std::string& idNo);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    virtual ~User() = default;
};
