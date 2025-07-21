#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class ViewSpecificCustomerAccount;
}

class ViewSpecificCustomerAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSpecificCustomerAccount(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~ViewSpecificCustomerAccount();
    void resetFields();
private:
    Ui::ViewSpecificCustomerAccount *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
    void on_search_btn_clicked();
};
