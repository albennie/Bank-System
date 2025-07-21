#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class ViewAllBankAccounts;
}

class ViewAllBankAccounts : public QWidget
{
    Q_OBJECT

public:
    explicit ViewAllBankAccounts(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~ViewAllBankAccounts();
    void populateTables();
private:
    Ui::ViewAllBankAccounts *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
};
