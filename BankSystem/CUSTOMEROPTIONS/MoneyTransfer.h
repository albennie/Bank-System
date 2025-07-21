#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class MoneyTransfer;
}

class MoneyTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit MoneyTransfer(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~MoneyTransfer();

    void moneyT();
signals:
    void backToDashboardRequested();

private slots:
    void on_logout_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MoneyTransfer *ui;
    std::shared_ptr<BankSystem> bankSystem;
    std::shared_ptr<Customer> currentCustomer;
    std::shared_ptr<Customer> recipient = nullptr;
    std::shared_ptr<BankAccount> recipientAccount = nullptr;


};
