#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class EditCustomerInfo;
}

class EditCustomerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit EditCustomerInfo(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~EditCustomerInfo();
    void resetFields();

private:
    Ui::EditCustomerInfo *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
    void on_search_btn_clicked();
    void on_register_btn_clicked();
    void on_delete_account_btn_clicked();
};
