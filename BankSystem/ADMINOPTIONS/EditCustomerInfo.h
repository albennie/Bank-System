#pragma once

#include <QWidget>

namespace Ui {
class EditCustomerInfo;
}

class EditCustomerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit EditCustomerInfo(QWidget *parent = nullptr);
    ~EditCustomerInfo();

private:
    Ui::EditCustomerInfo *ui;
};
