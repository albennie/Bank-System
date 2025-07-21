#include "ViewAllCustomers.h"
#include "ui_ViewAllCustomers.h"

ViewAllCustomers::ViewAllCustomers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewAllCustomers)
{
    ui->setupUi(this);
}

ViewAllCustomers::~ViewAllCustomers()
{
    delete ui;
}
