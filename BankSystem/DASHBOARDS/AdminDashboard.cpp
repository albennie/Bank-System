#include "AdminDashboard.h"
#include "ui_AdminDashboard.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}
