#pragma once

#include <QWidget>

namespace Ui {
class ViewAllCustomers;
}

class ViewAllCustomers : public QWidget
{
    Q_OBJECT

public:
    explicit ViewAllCustomers(QWidget *parent = nullptr);
    ~ViewAllCustomers();

private:
    Ui::ViewAllCustomers *ui;
};
