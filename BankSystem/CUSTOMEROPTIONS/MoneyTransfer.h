#pragma once

#include <QWidget>

namespace Ui {
class MoneyTransfer;
}

class MoneyTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit MoneyTransfer(QWidget *parent = nullptr);
    ~MoneyTransfer();

private:
    Ui::MoneyTransfer *ui;
};
