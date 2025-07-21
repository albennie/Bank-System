#include "C_ViewSpecificBankAccount.h"
#include "ui_C_ViewSpecificBankAccount.h"

C_ViewSpecificBankAccount::C_ViewSpecificBankAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::C_ViewSpecificBankAccount)
{
    ui->setupUi(this);
}

C_ViewSpecificBankAccount::~C_ViewSpecificBankAccount()
{
    delete ui;
}
