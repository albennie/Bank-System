#pragma once

#include <QMainWindow>

namespace Ui {
class CustomerDashboard;
}

class CustomerDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerDashboard(QWidget *parent = nullptr);
    ~CustomerDashboard();

private:
    Ui::CustomerDashboard *ui;
};
