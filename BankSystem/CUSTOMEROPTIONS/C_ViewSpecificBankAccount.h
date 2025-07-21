#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class C_ViewSpecificBankAccount;
}

class C_ViewSpecificBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit C_ViewSpecificBankAccount(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~C_ViewSpecificBankAccount();
    void ShowBankAccountInfo();

signals:
    void backToDashboardRequested();

private slots:
    void on_logout_clicked();

private:
    Ui::C_ViewSpecificBankAccount *ui;
    std::shared_ptr<BankSystem> bankSystem;
};
