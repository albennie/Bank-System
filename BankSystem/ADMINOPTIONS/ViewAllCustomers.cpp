#include "ADMINOPTIONS/ViewAllCustomers.h"
#include "ui_ViewAllCustomers.h"

ViewAllCustomers::ViewAllCustomers(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewAllCustomers)
    , bankSystem(system)
{
    ui->setupUi(this);
}

ViewAllCustomers::~ViewAllCustomers()
{
    delete ui;
}

void ViewAllCustomers::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}

void ViewAllCustomers::displayAllCustomers()
{
    auto customers = bankSystem->getCustomers();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);

    QStringList headers;
    headers << "Full Name" << "ID" << "Accounts Count" << "Total Balance";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < customers.GetSize(); ++i)
    {
        const auto& customer = customers[i];
        const auto& accounts = customer->getAccounts();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        long long totalBalance = 0;
        for (int j = 0; j < accounts.GetSize(); ++j)
            totalBalance += accounts[j]->getAccountBalance();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(customer->getFirstName() + " " + customer->getLastName())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customer->getIdNo())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(accounts.GetSize())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(totalBalance)));
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setTextElideMode(Qt::ElideNone);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setWordWrap(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}











