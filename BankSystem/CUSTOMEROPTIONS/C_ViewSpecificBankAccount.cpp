#include "C_ViewSpecificBankAccount.h"
#include "ui_C_ViewSpecificBankAccount.h"

C_ViewSpecificBankAccount::C_ViewSpecificBankAccount(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::C_ViewSpecificBankAccount)
    , bankSystem(system)
{
    ui->setupUi(this);
}

C_ViewSpecificBankAccount::~C_ViewSpecificBankAccount()
{
    delete ui;
}

void C_ViewSpecificBankAccount::on_logout_clicked()
{
    emit backToDashboardRequested();

}

void C_ViewSpecificBankAccount::ShowBankAccountInfo()
{
    ui->account_type_2->clear();
    ui->AN_2->setText("Account Number");
    ui->Balance_2->clear();
    ui->CCV2_2->clear();
    ui->Date_2->clear();
    ui->CN_2->setText("Card Number");
    ui->name_label->clear();
    ui->id_label->clear();
    ui->IBAN_2->setText("IBAN");
    ui->comboBox->clear();
    ui->comboBox->addItem("Choose any account to show its Info");


    auto c = bankSystem->getCurrentCustomer();
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
