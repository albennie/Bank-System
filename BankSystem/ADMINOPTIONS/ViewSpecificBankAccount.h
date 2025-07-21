#pragma once

#include <QWidget>

namespace Ui {
class ViewSpecificBankAccount;
}

class ViewSpecificBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSpecificBankAccount(QWidget *parent = nullptr);
    ~ViewSpecificBankAccount();

private:
    Ui::ViewSpecificBankAccount *ui;
};
