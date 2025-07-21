#pragma once

#include <QWidget>

namespace Ui {
class AddNewCustomer;
}

class AddNewCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewCustomer(QWidget *parent = nullptr);
    ~AddNewCustomer();

private:
    Ui::AddNewCustomer *ui;
};
