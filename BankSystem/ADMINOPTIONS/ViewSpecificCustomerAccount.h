#pragma once

#include <QWidget>

namespace Ui {
class ViewSpecificCustomerAccount;
}

class ViewSpecificCustomerAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSpecificCustomerAccount(QWidget *parent = nullptr);
    ~ViewSpecificCustomerAccount();

private:
    Ui::ViewSpecificCustomerAccount *ui;
};
