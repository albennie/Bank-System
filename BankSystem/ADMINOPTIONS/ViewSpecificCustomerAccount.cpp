#include "ADMINOPTIONS/ViewSpecificCustomerAccount.h"
#include "ui_ViewSpecificCustomerAccount.h"
#include "QMessageBox"

ViewSpecificCustomerAccount::ViewSpecificCustomerAccount(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewSpecificCustomerAccount)
    , bankSystem(system)
{
    ui->setupUi(this);
}

ViewSpecificCustomerAccount::~ViewSpecificCustomerAccount()
{
    delete ui;
}

void ViewSpecificCustomerAccount::on_logoutButton_clicked()
{
    emit backToDashboardRequested();
}

void ViewSpecificCustomerAccount::resetFields()
{
    ui->account_type_2->clear();
    ui->AN_2->setText("Account Number");
    ui->Balance_2->clear();
    ui->CCV2_2->clear();
    ui->Date_2->clear();
    ui->CN_2->setText("Card Number");
    ui->ID_Line->clear();
    ui->name_label->clear();
    ui->id_label->clear();
    ui->IBAN_2->setText("IBAN");
    ui->comboBox->clear();
    ui->comboBox->addItem("Choose any account to show its Info");
    ui->widget_2->hide();
    ui->widget->show();
}

void ViewSpecificCustomerAccount::on_search_btn_clicked()
{
    QString ID = ui->ID_Line->text();

    auto ll = bankSystem->getCustomers();

    shared_ptr<Customer> c = nullptr;
    int i = 0;

    for (i = 0; i < ll.GetSize(); i++)
    {
        if (ll[i]->getIdNo() == ID.toStdString())
        {
            c = ll[i];
            break;
        }
    }

    if (ll.GetSize() == i)
    {
        QMessageBox::warning(this, "Error", "There's no customer with this ID!");
    }
    else
    {
        ui->widget->hide();
        ui->widget_2->show();
        ui->name_label->setText(QString::fromStdString(c->getFirstName() + " " + c->getLastName()));
        ui->id_label->setText(QString::fromStdString(c->getIdNo()));

        auto accounts = c->getAccounts();

        for (int i = 0; i < accounts.GetSize(); i++)
        {
            ui->comboBox->addItem(QString::fromStdString(
                accounts[i]->getCardNumber() + " (" + accounts[i]->AccountType() + ")"
                ));
        }

        connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [=]() {
                    int index = ui->comboBox->currentIndex();
                    if (index > 0 && index <= accounts.GetSize())
                    {
                        auto acc = accounts[index - 1];
                        if(acc->AccountType() == "Savings Account")
                        {
                            dynamic_pointer_cast<SavingsAccount>(acc)->applyInterest();
                        }
                        ui->AN_2->setText(QString::fromStdString(acc->getAccountNumber()));
                        ui->Date_2->setText(QString::fromStdString(acc->getExpirationYear() + "/" + acc->getExpirationMonth()));
                        ui->CCV2_2->setText(QString::fromStdString(acc->getCVV2()));
                        ui->CN_2->setText(QString::fromStdString(acc->getCardNumber()));
                        ui->IBAN_2->setText(QString::fromStdString(acc->getIBANnumber()));
                        ui->Balance_2->setText(QString::number(acc->getAccountBalance()));
                        ui->account_type_2->setText(QString::fromStdString(acc->AccountType()));
                    }
                    else
                    {
                        ui->account_type_2->clear();
                        ui->AN_2->setText("Account Number");
                        ui->Balance_2->clear();
                        ui->CCV2_2->clear();
                        ui->Date_2->clear();
                        ui->CN_2->setText("Card Number");
                        ui->IBAN_2->setText("IBAN");
                    }
                });
    }
}
