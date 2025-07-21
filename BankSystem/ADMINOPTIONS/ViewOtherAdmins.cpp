#include "ADMINOPTIONS/ViewOtherAdmins.h"
#include "ui_ViewOtherAdmins.h"

ViewOtherAdmins::ViewOtherAdmins(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewOtherAdmins)
    , bankSystem(system)
{
    ui->setupUi(this);
}

ViewOtherAdmins::~ViewOtherAdmins()
{
    delete ui;
}

void ViewOtherAdmins::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}

void ViewOtherAdmins::displayAllAdmins()
{
    auto admins = bankSystem->getAdmins();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);

    QStringList headers;
    headers << "Full Name" << "ID" << "Username" << "Birth Year";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < admins.GetSize(); ++i)
    {

        const auto& admin = admins[i];

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(admin->getFirstName() + " " + admin->getLastName())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(admin->getIdNo())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(admin->getUsername())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(admin->getAgeYear())));
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setTextElideMode(Qt::ElideNone);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setWordWrap(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}
