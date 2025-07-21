#include "EditCustomerInfo.h"
#include "ui_EditCustomerInfo.h"

EditCustomerInfo::EditCustomerInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditCustomerInfo)
{
    ui->setupUi(this);
}

EditCustomerInfo::~EditCustomerInfo()
{
    delete ui;
}
