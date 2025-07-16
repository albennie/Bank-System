#include "LoginForm.h"
#include "ui_LoginForm.h"

LoginForm::LoginForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}
