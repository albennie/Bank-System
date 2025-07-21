#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class AddNewCustomer;
}

class AddNewCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewCustomer(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~AddNewCustomer();
    void resetFields();

private:
    Ui::AddNewCustomer *ui;
    std::shared_ptr<BankSystem> bankSystem;

signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
    void on_Add_btn_clicked();
};
