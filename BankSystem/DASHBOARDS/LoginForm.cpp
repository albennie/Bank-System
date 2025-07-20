#include "LoginForm.h"
#include "ui_LoginForm.h"
#include "CustomerDashboard.h"

LoginForm::LoginForm(std::shared_ptr<BankSystem> system,QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoginForm)
{
        bankSystem = system;
        ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginButton_clicked()
{
    QString username = ui->user->text();
    QString password = ui->pass->text();

    if (bankSystem->login(username.toStdString(), password.toStdString())) {
        this->hide();

        if (bankSystem->isAdminLoggedIn())
        {
            adminUI = new AdminDashboard(bankSystem, this);
            connect(adminUI, &AdminDashboard::logoutRequested, this, &LoginForm::showAgain);
            adminUI->show();
        } else {
            customerUI = new CustomerDashboard(bankSystem, this);
            connect(customerUI, &CustomerDashboard::logoutRequested, this, &LoginForm::showAgain);
            customerUI->show();
        }
    } else {
        ui->errorLabel->setText("Wrong Data!");
    }
}

void LoginForm::showAgain() {
    if (customerUI) {
        customerUI->close();
        delete customerUI;
        customerUI = nullptr;
    }
    if (adminUI) {
        adminUI->close();
        delete adminUI;
        adminUI = nullptr;
    }
    bankSystem->logout();
    this->ui->pass->setText("");
    this->ui->user->setText("");
    ui->errorLabel->setText("");
    this->show();
}


