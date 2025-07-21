#include "AddBankAccount.h"
#include "ui_AddBankAccount.h"

AddBankAccount::AddBankAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBankAccount)
{
    ui->setupUi(this);
}

AddBankAccount::~AddBankAccount()
{
    delete ui;
}
