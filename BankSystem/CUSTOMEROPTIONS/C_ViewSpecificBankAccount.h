#pragma once

#include <QWidget>

namespace Ui {
class C_ViewSpecificBankAccount;
}

class C_ViewSpecificBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit C_ViewSpecificBankAccount(QWidget *parent = nullptr);
    ~C_ViewSpecificBankAccount();

private:
    Ui::C_ViewSpecificBankAccount *ui;
};
