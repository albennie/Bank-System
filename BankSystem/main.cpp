#include "DASHBOARDS/LoginForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    shared_ptr<BankSystem> system = make_shared<BankSystem>();
    LoginForm login(system);
    login.show();

    return a.exec();
}
