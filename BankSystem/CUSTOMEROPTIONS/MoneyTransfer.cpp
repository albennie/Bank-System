#include "MoneyTransfer.h"
#include "ui_MoneyTransfer.h"

MoneyTransfer::MoneyTransfer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoneyTransfer)
{
    ui->setupUi(this);
}

MoneyTransfer::~MoneyTransfer()
{
    delete ui;
}
