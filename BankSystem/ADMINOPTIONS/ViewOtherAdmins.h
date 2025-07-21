#pragma once

#include <QWidget>

namespace Ui {
class ViewOtherAdmins;
}

class ViewOtherAdmins : public QWidget
{
    Q_OBJECT

public:
    explicit ViewOtherAdmins(QWidget *parent = nullptr);
    ~ViewOtherAdmins();

private:
    Ui::ViewOtherAdmins *ui;
};
