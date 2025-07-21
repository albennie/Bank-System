#include <random>
#include <ctime>
#include <sstream>
#include <QIntValidator>

#include "ADMINOPTIONS/AddBankAccount.h"
#include "ui_AddBankAccount.h"
#include "QMessageBox"

AddBankAccount::AddBankAccount(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBankAccount)
    , bankSystem(system)
{
    ui->setupUi(this);
}

AddBankAccount::~AddBankAccount()
{
    delete ui;
}

void AddBankAccount::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}

void AddBankAccount::resetFields()
{
    ui->comboBox->setEnabled(true);
    ui->lineEdit->clear();
    ui->AN_LineEdit->clear();
    ui->Balance_LineEdit->clear();
    ui->CN_LineEdit->clear();
    ui->IBAN_LineEdit->clear();
    ui->PIN_LineEdit->clear();
    ui->SSP_LineEdit->clear();
    ui->getID_lineEdit->clear();
    ui->dateEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->widget_2->hide();
    ui->widget->show();
}

void AddBankAccount::on_getID_btn_clicked()
{
    QString ID = ui->getID_lineEdit->text();

    auto ll = bankSystem->getCustomers();

    shared_ptr<Customer> c = nullptr;
    int i = 0;

    for(i = 0;i < ll.GetSize();i++)
        if(ll[i]->getIdNo() == ID.toStdString())
        {
            c = ll[i];
            break;
        }

    if(ll.GetSize() == i)
    {
        QMessageBox::warning(this,"Error","There's no customer with this ID!");
    }
    else if(c->getAccountNumber() >= 5)
    {
        QMessageBox::warning(this,"Error","This customer has 5 Bank Accounts!");
    }
    else
    {
        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit->setMinimumDate(QDate::currentDate());
        ui->Balance_LineEdit->setValidator(new QIntValidator(1, INT_MAX, this));

        ui->widget->hide();
        ui->widget_2->show();
        ui->customerName_Label->setText(QString::fromStdString(c->getFirstName() + " " + c->getLastName()));

        ui->Balance_LineEdit->setPlaceholderText("Please select from above");
        ui->SSP_LineEdit->setPlaceholderText("Please select from above");
        ui->PIN_LineEdit->setPlaceholderText("Please select from above");
        ui->SSP_LineEdit->setEnabled(false);
        ui->PIN_LineEdit->setEnabled(false);
        ui->Balance_LineEdit->setEnabled(false);
        ui->splitter->setEnabled(false);


        connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [&]() {
            if(ui->comboBox->currentIndex() == 1 ||
                ui->comboBox->currentIndex() == 2 ||
                ui->comboBox->currentIndex() == 3)
            {
                ui->comboBox->setEnabled(false);
                ui->Balance_LineEdit->setPlaceholderText("");
                ui->SSP_LineEdit->setPlaceholderText("");
                ui->PIN_LineEdit->setPlaceholderText("");
                ui->SSP_LineEdit->setEnabled(true);
                ui->PIN_LineEdit->setEnabled(true);
                ui->Balance_LineEdit->setEnabled(true);
                ui->splitter->setEnabled(true);

                auto isCardNumberUnique = [&](const std::string& cardNum) -> bool {
                    for (int i = 0; i < bankSystem->getCustomers().GetSize(); ++i) {
                        auto c = bankSystem->getCustomers()[i];
                        for (int j = 0; j < c->getAccountNumber(); ++j) {
                            if (c->getAccounts()[j]->getCardNumber() == cardNum)
                                return false;
                        }
                    }
                    return true;
                };

                auto isIBANUnique = [&](const std::string& iban) -> bool {
                    for (int i = 0; i < bankSystem->getCustomers().GetSize(); ++i) {
                        auto c = bankSystem->getCustomers()[i];
                        for (int j = 0; j < c->getAccountNumber(); ++j) {
                            if (c->getAccounts()[j]->getIBANnumber() == iban)
                                return false;
                        }
                    }
                    return true;
                };

                auto isAccountNumberUnique = [&](const std::string& accNum) -> bool {
                    for (int i = 0; i < bankSystem->getCustomers().GetSize(); ++i) {
                        auto c = bankSystem->getCustomers()[i];
                        for (int j = 0; j < c->getAccountNumber(); ++j) {
                            if (c->getAccounts()[j]->getAccountNumber() == accNum)
                                return false;
                        }
                    }
                    return true;
                };

                std::string cardNum;
                do {
                    std::ostringstream s1;
                    for (int i = 0; i < 16; ++i)
                        s1 << std::uniform_int_distribution<>(0, 9)(funk());
                    cardNum = s1.str();
                } while (!isCardNumberUnique(cardNum));
                ui->CN_LineEdit->setText(QString::fromStdString(cardNum));

                std::string iban;
                do {
                    std::ostringstream s2;
                    s2 << "IR";
                    for (int i = 0; i < 24; ++i)
                        s2 << std::uniform_int_distribution<>(0, 9)(funk());
                    iban = s2.str();
                } while (!isIBANUnique(iban));
                ui->IBAN_LineEdit->setText(QString::fromStdString(iban));

                std::string accNum;
                do {
                    std::ostringstream ss;
                    for (int i = 0; i < 13; ++i)
                        ss << std::uniform_int_distribution<>(0, 9)(funk());
                    accNum = ss.str();
                } while (!isAccountNumberUnique(accNum));
                ui->AN_LineEdit->setText(QString::fromStdString(accNum));


                ui->lineEdit->setText(QString::fromStdString(std::to_string(std::uniform_int_distribution<>(1000, 9999)(funk()))));
            }
                });
    }
}

std::mt19937& AddBankAccount::funk() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

void AddBankAccount::on_Add_btn_clicked()
{
    auto cll = bankSystem->getCustomers();
    std::shared_ptr<Customer> customer = nullptr;

    std::string fullName = ui->customerName_Label->text().toStdString();
    for (int i = 0; i < cll.GetSize(); ++i)
    {
        std::string currentFullName = cll[i]->getFirstName() + " " + cll[i]->getLastName();
        if (currentFullName == fullName)
        {
            customer = cll[i];
            break;
        }
    }

    if (!customer) {
        QMessageBox::warning(this, "Error", "Customer not found!");
        return;
    }

    QString cardNumber = ui->CN_LineEdit->text();
    QString iban = ui->IBAN_LineEdit->text();
    QString accNumber = ui->AN_LineEdit->text();
    QString ccv2 = ui->lineEdit->text();
    QString pin = ui->PIN_LineEdit->text();
    QString staticPass = ui->SSP_LineEdit->text();

    int balance = ui->Balance_LineEdit->text().toInt();

    QString expMonth = QString("%1").arg(ui->dateEdit->date().month() - 2 , 2, 10, QLatin1Char('0'));
    QString expYear = QString("%1").arg((ui->dateEdit->date().year() % 100) - 21 , 2, 10, QLatin1Char('0'));

    if (ui->comboBox->currentIndex() == 0) {
        QMessageBox::warning(this, "Error", "Please select an account type.");
        return;
    }
    if (pin.length() < 4 || staticPass.length() < 5) {
        QMessageBox::warning(this, "Error", "Check the length of PIN and Static Password.");
        return;
    }

    std::shared_ptr<BankAccount> newAccount;

    switch (ui->comboBox->currentIndex()) {
    case 1:
        newAccount = std::make_shared<SavingsAccount>(cardNumber.toStdString(), iban.toStdString(), accNumber.toStdString(),
                                                      ccv2.toStdString(), expYear.toStdString(), expMonth.toStdString(),
                                                      pin.toStdString(), staticPass.toStdString(), balance);
        break;
    case 2:
        newAccount = std::make_shared<CheckingAccount>(cardNumber.toStdString(), iban.toStdString(), accNumber.toStdString(),
                                                       ccv2.toStdString(), expYear.toStdString(), expMonth.toStdString(),
                                                       pin.toStdString(), staticPass.toStdString(), balance);
        break;
    case 3:
        newAccount = std::make_shared<Qarz_al_HasanAccount>(cardNumber.toStdString(), iban.toStdString(), accNumber.toStdString(),
                                                            ccv2.toStdString(), expYear.toStdString(), expMonth.toStdString(),
                                                            pin.toStdString(), staticPass.toStdString(), balance);
        break;
    }

    if (!newAccount) {
        QMessageBox::warning(this, "Error", "Failed to create account!");
        return;
    }

    if (!customer->addAccount(newAccount)) {
        QMessageBox::warning(this, "Limit Exceeded", "Customer already has 5 accounts.");
        return;
    }

    QMessageBox::information(this, "Success", "Account added successfully!");
    emit backToDashboardRequested();
}





















