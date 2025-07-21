#include "ADMINOPTIONS/EditCustomerInfo.h"
#include "ui_EditCustomerInfo.h"
#include "QMessageBox"

EditCustomerInfo::EditCustomerInfo(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditCustomerInfo)
    , bankSystem(system)
{
    ui->setupUi(this);
}

EditCustomerInfo::~EditCustomerInfo()
{
    delete ui;
}

void EditCustomerInfo::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}

void EditCustomerInfo::resetFields()
{
    ui->new_password_lineEdit->clear();
    ui->new_username_lineEdit->clear();
    ui->ID_Line->clear();
    ui->ID_Line->clear();
    ui->Age_label->clear();
    ui->Accounts_number_label->clear();
    ui->name_label->clear();
    ui->comboBox->clear();
    ui->comboBox->addItem("select option...(Leave to not change)");
    ui->widget->show();
    ui->widget_2->hide();
}


void EditCustomerInfo::on_search_btn_clicked()
{
    QString ID = ui->ID_Line->text();

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
    else
    {
        ui->widget->hide();
        ui->widget_2->show();
        ui->name_label->setText(QString::fromStdString(c->getFirstName() + " " + c->getLastName()));
        ui->ID_label->setText(QString::fromStdString(c->getIdNo()));
        ui->Accounts_number_label->setText(QString::fromStdString(to_string(c->getAccountNumber())));
        ui->Age_label->setText(QString::fromStdString(to_string(1404 - c->getAgeYear())));
        int i = 0;
        auto accounts = c->getAccounts();
        for(i = 0;i<c->getAccountNumber();i++)
        {
            ui->comboBox->addItem(QString::fromStdString(accounts[i]->getCardNumber() + " (" + accounts[i]->AccountType() + ")" ));
        }

    }
}


void EditCustomerInfo::on_register_btn_clicked()
{
    QString username = ui->new_username_lineEdit->text();
    QString password = ui->new_password_lineEdit->text();
    QString ID = ui->ID_label->text();

    auto customers = bankSystem->getCustomers();
    std::shared_ptr<Customer> c = nullptr;

    for (int i = 0; i < customers.GetSize(); ++i)
    {
        if (customers[i]->getIdNo() == ID.toStdString()) {
            c = customers[i];
            break;
        }
    }

    if (!c) {
        QMessageBox::warning(this, "Error", "Customer not found.");
        return;
    }

    if (!username.isEmpty()) {
        bool usernameTaken = false;
        for (int i = 0; i < customers.GetSize(); ++i) {
            if (customers[i]->getUsername() == username.toStdString()) {
                usernameTaken = true;
                break;
            }
        }

        if (usernameTaken) {
            QMessageBox::warning(this, "Error", "Try another username.");
            return;
        }

        c->setUsername(username.toStdString());
    }

    if (!password.isEmpty()) {
        c->setPassword(password.toStdString());
    }

    int index = ui->comboBox->currentIndex();
    if (index >= 1) {
        QString selected = ui->comboBox->currentText();
        std::string cardNumber = selected.toStdString().substr(0, 16);
        c->removeAccount(cardNumber);
    }

    QMessageBox::information(this, "Success", "Changes registered successfully!");
    emit backToDashboardRequested();
}


void EditCustomerInfo::on_delete_account_btn_clicked()
{
    QString id = ui->ID_label->text();

    auto reply = QMessageBox::question(this, "Confirm", "Are you sure you want to delete this customer?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bankSystem->removeCustomerById(id.toStdString());
        QMessageBox::information(this, "Success", "Customer Removed Successfully!");
        emit backToDashboardRequested();
    }
}

























