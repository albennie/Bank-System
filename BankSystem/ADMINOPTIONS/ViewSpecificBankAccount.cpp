#include "ViewSpecificBankAccount.h"
#include "ui_ViewSpecificBankAccount.h"

ViewSpecificBankAccount::ViewSpecificBankAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewSpecificBankAccount)
{
    ui->setupUi(this);
}

ViewSpecificBankAccount::~ViewSpecificBankAccount()
{
    delete ui;
}
