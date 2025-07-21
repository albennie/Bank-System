#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class ViewAllCustomers;
}

class ViewAllCustomers : public QWidget
{
    Q_OBJECT

public:
    explicit ViewAllCustomers(std::shared_ptr<BankSystem> system,QWidget *parent = nullptr);
    ~ViewAllCustomers();
    void displayAllCustomers();

private:
    Ui::ViewAllCustomers *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
};
