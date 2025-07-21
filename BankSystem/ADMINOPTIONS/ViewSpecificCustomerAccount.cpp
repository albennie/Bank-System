#include "ViewSpecificCustomerAccount.h"
#include "ui_ViewSpecificCustomerAccount.h"

ViewSpecificCustomerAccount::ViewSpecificCustomerAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewSpecificCustomerAccount)
{
    ui->setupUi(this);
}

ViewSpecificCustomerAccount::~ViewSpecificCustomerAccount()
{
    delete ui;
}
