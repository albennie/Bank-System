#pragma once

#include <QWidget>

namespace Ui {
class ViewAllBankAccounts;
}

class ViewAllBankAccounts : public QWidget
{
    Q_OBJECT

public:
    explicit ViewAllBankAccounts(QWidget *parent = nullptr);
    ~ViewAllBankAccounts();

private:
    Ui::ViewAllBankAccounts *ui;
};
