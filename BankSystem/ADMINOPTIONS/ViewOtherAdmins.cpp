#include "ViewOtherAdmins.h"
#include "ui_ViewOtherAdmins.h"

ViewOtherAdmins::ViewOtherAdmins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewOtherAdmins)
{
    ui->setupUi(this);
}

ViewOtherAdmins::~ViewOtherAdmins()
{
    delete ui;
}
