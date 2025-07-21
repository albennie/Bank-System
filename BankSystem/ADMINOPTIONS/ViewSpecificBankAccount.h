#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class ViewSpecificBankAccount;
}

class ViewSpecificBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSpecificBankAccount(std::shared_ptr<BankSystem> system,QWidget *parent = nullptr);
    ~ViewSpecificBankAccount();
    void resetFields();


private:
    Ui::ViewSpecificBankAccount *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
    void on_pushButton_2_clicked();
};
