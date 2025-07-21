#include "AddNewCustomer.h"
#include "ui_AddNewCustomer.h"

AddNewCustomer::AddNewCustomer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddNewCustomer)
{
    ui->setupUi(this);
}

AddNewCustomer::~AddNewCustomer()
{
    delete ui;
}
