#pragma once

#include <QWidget>

namespace Ui {
class AddBankAccount;
}

class AddBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit AddBankAccount(QWidget *parent = nullptr);
    ~AddBankAccount();

private:
    Ui::AddBankAccount *ui;
};
