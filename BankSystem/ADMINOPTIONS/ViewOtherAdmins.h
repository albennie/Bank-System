#pragma once

#include <QWidget>
#include "BankSystem.h"

namespace Ui {
class ViewOtherAdmins;
}

class ViewOtherAdmins : public QWidget
{
    Q_OBJECT

public:
    explicit ViewOtherAdmins(std::shared_ptr<BankSystem> system,QWidget *parent = nullptr);
    ~ViewOtherAdmins();
    void displayAllAdmins();
private:
    Ui::ViewOtherAdmins *ui;
    std::shared_ptr<BankSystem> bankSystem;
signals:
    void backToDashboardRequested();
private slots:
    void on_logoutButton_clicked();
};
