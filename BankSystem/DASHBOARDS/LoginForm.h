#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginForm;
}
QT_END_NAMESPACE

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
};
