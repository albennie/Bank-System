#include "ADMINOPTIONS/ViewSpecificBankAccount.h"
#include "ui_ViewSpecificBankAccount.h"
#include "QMessageBox"

ViewSpecificBankAccount::ViewSpecificBankAccount(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewSpecificBankAccount)
    , bankSystem(system)
{
    ui->setupUi(this);
}

ViewSpecificBankAccount::~ViewSpecificBankAccount()
{
    delete ui;
}

void ViewSpecificBankAccount::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}
void ViewSpecificBankAccount::resetFields()
{
    ui->AN->clear();
    ui->Balance->clear();
    ui->CCV2->clear();
    ui->CN->clear();
    ui->Date->clear();
    ui->IBAN->clear();
    ui->id->clear();
    ui->name->clear();
    ui->lineEdit->clear();
    ui->groupBox->hide();
    ui->widget->show();
}


void ViewSpecificBankAccount::on_pushButton_2_clicked()
{
    QString cardNumber = ui->lineEdit->text().trimmed();

    if (cardNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a card number.");
        return;
    }

    auto customers = bankSystem->getCustomers();
    std::shared_ptr<BankAccount> foundAccount = nullptr;
    std::shared_ptr<Customer> owner = nullptr;

    for (int i = 0; i < customers.GetSize(); ++i) {
        auto accounts = customers[i]->getAccounts();
        for (int j = 0; j < accounts.GetSize(); ++j) {
            if (accounts[j]->getCardNumber() == cardNumber.toStdString()) {
                foundAccount = accounts[j];
                owner = customers[i];
                break;
            }
        }
        if (foundAccount) break;
    }

    if (foundAccount && owner) {
        if(foundAccount->AccountType() == "Savings Account")
        {
            dynamic_pointer_cast<SavingsAccount>(foundAccount)->applyInterest();
        }
        ui->CN->setText(QString::fromStdString(foundAccount->getCardNumber()));
        ui->AN->setText(QString::fromStdString(foundAccount->getAccountNumber()));
        ui->IBAN->setText(QString::fromStdString(foundAccount->getIBANnumber()));
        ui->CCV2->setText(QString::fromStdString(foundAccount->getCVV2()));
        ui->Date->setText(QString::fromStdString(foundAccount->getExpirationYear() + "/" + foundAccount->getExpirationMonth() ));
        ui->Balance->setText(QString::number(foundAccount->getAccountBalance()));
        ui->account_type->setText(QString::fromStdString(foundAccount->AccountType()));
        ui->name->setText(QString::fromStdString(owner->getFirstName() + " " + owner->getLastName()));
        ui->id->setText(QString::fromStdString(owner->getIdNo()));

        ui->groupBox->show();
        ui->widget->hide();
    } else {
        QMessageBox::warning(this, "Not Found", "No account found with this card number.");
    }
}






























