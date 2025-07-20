#pragma once
#include "AdminDashboard.h"
#include <memory>
#include <BASECLASSES/BankSystem.h>
#include <QMainWindow>
#include <CustomerDashboard.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginForm;
}
QT_END_NAMESPACE

class LoginForm : public QMainWindow
{
    Q_OBJECT

private:
    Ui::LoginForm *ui;
    std::shared_ptr<BankSystem> bankSystem;
    AdminDashboard* adminUI = nullptr;
    CustomerDashboard* customerUI = nullptr;

public:
    LoginForm(std::shared_ptr<BankSystem> system ,QWidget* parent = nullptr);
    ~LoginForm();
    void showAgain();

private slots:
    void on_loginButton_clicked();
};
