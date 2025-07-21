#include "ViewAllBankAccounts.h"
#include "ui_ViewAllBankAccounts.h"

ViewAllBankAccounts::ViewAllBankAccounts(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewAllBankAccounts)
{
    ui->setupUi(this);
}

ViewAllBankAccounts::~ViewAllBankAccounts()
{
    delete ui;
}
