#pragma once

#include <QCloseEvent>
#include <QMainWindow>
#include <memory>
#include "BankSystem.h"
#include "CUSTOMEROPTIONS/C_ViewSpecificBankAccount.h"
#include "CUSTOMEROPTIONS/MoneyTransfer.h"


namespace Ui { class CustomerDashboard; }

class CustomerDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit CustomerDashboard(std::shared_ptr<BankSystem> system, QWidget *parent = nullptr);
    ~CustomerDashboard();
protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void logoutRequested();

private slots:
    void on_logoutButton_clicked();

    void on_change_pin_clicked();

    void on_change_static_pass_clicked();

    void on_change_info_clicked();

private:
    Ui::CustomerDashboard *ui;
    std::shared_ptr<BankSystem> bankSystem;

    C_ViewSpecificBankAccount* viewSpecificAccount;
    MoneyTransfer* moneyTransfer;
};
