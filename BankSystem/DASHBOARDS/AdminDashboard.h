#pragma once

#include <QCloseEvent>
#include <QMainWindow>
#include "BankSystem.h"
#include "ADMINOPTIONS/ViewOtherAdmins.h"
#include "ADMINOPTIONS/ViewAllBankAccounts.h"
#include "ADMINOPTIONS/ViewSpecificBankAccount.h"
#include "ADMINOPTIONS/ViewAllCustomers.h"
#include "ADMINOPTIONS/ViewSpecificCustomerAccount.h"
#include "ADMINOPTIONS/AddNewCustomer.h"
#include "ADMINOPTIONS/AddBankAccount.h"
#include "ADMINOPTIONS/EditCustomerInfo.h"


namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminDashboard(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~AdminDashboard();

signals:
    void logoutRequested();
protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void on_logoutButton_clicked();

    void on_edit_your_info_clicked();

private:
    Ui::AdminDashboard *ui;
    std::shared_ptr<BankSystem> bankSystem;

    AddNewCustomer* addNewCustomerPage;
    ViewAllCustomers* viewAllCustomersPage;
    ViewSpecificCustomerAccount* viewSpecificCustomerPage;
    ViewAllBankAccounts* viewAllAccountsPage;
    ViewSpecificBankAccount* viewSpecificAccountPage;
    ViewOtherAdmins* viewOtherAdminsPage;
    AddBankAccount* addBankAccountoPage;
    EditCustomerInfo* editCustomerInfoPage;
};
