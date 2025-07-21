#include "MoneyTransfer.h"
#include "ui_MoneyTransfer.h"
#include <QMessageBox>
#include <ctime>
#include <cstdlib>
#include <QDate>

MoneyTransfer::MoneyTransfer(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::MoneyTransfer),
    bankSystem(system),
    currentCustomer(system->getCurrentCustomer()),
    recipient(nullptr),
    recipientAccount(nullptr)
{
    ui->setupUi(this);
}

void MoneyTransfer::moneyT()
{
    currentCustomer = bankSystem->getCurrentCustomer();
    recipient = nullptr;
    recipientAccount = nullptr;
    ui->label_5->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->groupBox->show();
    ui->widget->hide();
    ui->comboBox->clear();

    for (int i = 0; i < bankSystem->getCurrentCustomer()->getAccountNumber(); ++i) {
        auto acc = currentCustomer->getAccounts()[i];
        if(acc->AccountType() == "Savings Account")
        {
            dynamic_pointer_cast<SavingsAccount>(acc)->applyInterest();
        }
        ui->comboBox->addItem(QString::fromStdString(acc->getCardNumber()+ " (" + to_string(acc->getAccountBalance()) + ")"));
    }
}



MoneyTransfer::~MoneyTransfer()
{
    delete ui;
}

void MoneyTransfer::on_logout_clicked()
{
    emit backToDashboardRequested();
}

void MoneyTransfer::on_pushButton_clicked()
{
    QString destCard = ui->lineEdit->text().trimmed();
    QString amountStr = ui->lineEdit_2->text().trimmed();
    bool useStatic = ui->radioButton->isChecked();
    bool useDynamic = ui->radioButton_2->isChecked();

    if (destCard.isEmpty() || amountStr.isEmpty() || (!useStatic && !useDynamic)) {
        QMessageBox::warning(this, "Error", "Fill all fields and select password type.");
        return;
    }

    bool ok = false;
    int amount = amountStr.toInt(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Error", "Enter a valid amount.");
        return;
    }

    if (amount > 3'000'000) {
        QMessageBox::warning(this, "Error", "Max per transaction is 3,000,000 Toman.");
        return;
    }

    recipient = nullptr;
    recipientAccount = nullptr;

    for (int i = 0; i < bankSystem->getCustomers().GetSize(); ++i) {
        auto c = bankSystem->getCustomers()[i];
        if (!c) continue;
        for (int j = 0; j < c->getAccountNumber(); ++j) {
            auto acc = c->getAccounts()[j];
            if (acc && acc->getCardNumber() == destCard.toStdString()) {
                recipient = c;
                recipientAccount = acc;
                break;
            }
        }
        if (recipient && recipientAccount) break;
    }

    if (!recipient || !recipientAccount) {
        QMessageBox::warning(this, "Error", "Invalid destination card number.");
        return;
    }

    int index = ui->comboBox->currentIndex();
    if (index < 0 || index >= currentCustomer->getAccountNumber()) {
        QMessageBox::critical(this, "Error", "No valid source account selected.");
        return;
    }

    auto fromAccount = currentCustomer->getAccounts()[index];
    if (!fromAccount) {
        QMessageBox::critical(this, "Error", "Source account not found.");
        return;
    }

    if(recipientAccount == fromAccount)
    {
        QMessageBox::critical(this, "Error", "recipient Account can not be The Source account!");
        return;
    }


    int expMonth = std::stoi(fromAccount->getExpirationMonth());
    int expYear = std::stoi(fromAccount->getExpirationYear());

    if (expYear < 4 || (expYear == 4 && expMonth < 5)) {
        QMessageBox::warning(this, "Error", "Source card has expired.");
        return;
    }

    if (useStatic && amount > 100'000) {
        QMessageBox::warning(this, "Error", "Max 100,000 allowed with static password.");
        return;
    }

    if (!recipient->getFirstName().empty() && !recipient->getLastName().empty()) {
        QString receiverName = QString::fromStdString(recipient->getFirstName() + " " + recipient->getLastName());
        ui->label_5->setText(receiverName);
    } else {
        ui->label_5->setText("Unknown");
    }

    if (!useStatic && useDynamic) {
        srand(static_cast<unsigned>(time(nullptr)));
        std::string otp = std::to_string(100000 + rand() % 900000);
        fromAccount->setDynamicSecondPassword(otp);
        QMessageBox::information(this, "OTP Generated", QString::fromStdString("Your OTP is: " + otp));
    }

    ui->groupBox->hide();
    ui->widget->show();
}


void MoneyTransfer::on_pushButton_3_clicked()
{
    if (!recipient || !recipientAccount) {
        QMessageBox::critical(this, "Error", "Transfer error: recipient data missing.");
        return;
    }

    int index = ui->comboBox->currentIndex();
    if (index < 0 || index >= currentCustomer->getAccountNumber()) {
        QMessageBox::critical(this, "Error", "No valid source account selected.");
        return;
    }

    auto fromAccount = currentCustomer->getAccounts()[index];
    if (!fromAccount) {
        QMessageBox::critical(this, "Error", "Source account is invalid.");
        return;
    }

    QString inputPass = ui->lineEdit_3->text();
    bool useStatic = ui->radioButton->isChecked();

    std::string rawPass = useStatic
                              ? fromAccount->getStaticSecondPassword()
                              : fromAccount->getDynamicSecondPassword();

    if (rawPass.empty()) {
        QMessageBox::warning(this, "Error", "Password field is empty.");
        return;
    }

    QString correctPass = QString::fromStdString(rawPass);


    if (inputPass != correctPass) {
        QMessageBox::warning(this, "Error", "Incorrect second password.");
        return;
    }

    bool ok = false;
    int amount = ui->lineEdit_2->text().toInt(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount.");
        return;
    }

    if (fromAccount->transferredLast24Hours() + amount > 6'000'000) {
        QMessageBox::warning(this, "Error", "You have exceeded the 6 million Toman daily transfer limit.");
        return;
    }

    int fee = static_cast<int>(amount * 0.0001);
    int totalDeduction = amount + fee;

    if (fromAccount->getAccountBalance() < totalDeduction) {
        QMessageBox::warning(this, "Error", "Insufficient funds (including transfer fee).");
        return;
    }

    fromAccount->withdraw(totalDeduction);
    recipientAccount->deposit(amount);
    fromAccount->setDynamicSecondPassword("");
    fromAccount->logTransfer(amount);

    QMessageBox::information(this, "Success", "Transfer completed successfully.");
    emit backToDashboardRequested();
}
