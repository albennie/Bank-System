#pragma once

#include <QWidget>
#include <random>
#include "BankSystem.h"

namespace Ui {
class AddBankAccount;
}

class AddBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit AddBankAccount(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~AddBankAccount();
    void resetFields();

private:
    Ui::AddBankAccount* ui;
    std::shared_ptr<BankSystem> bankSystem;
    static std::mt19937& funk();
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
    void on_getID_btn_clicked();
    void on_Add_btn_clicked();
};
