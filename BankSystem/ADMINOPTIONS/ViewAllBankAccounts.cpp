#include "ADMINOPTIONS/ViewAllBankAccounts.h"
#include "ui_ViewAllBankAccounts.h"

ViewAllBankAccounts::ViewAllBankAccounts(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewAllBankAccounts)
    , bankSystem(system)
{
    ui->setupUi(this);
}

ViewAllBankAccounts::~ViewAllBankAccounts()
{
    delete ui;
}

void ViewAllBankAccounts::on_logoutButton_clicked()
{
    emit backToDashboardRequested();

}

void ViewAllBankAccounts::populateTables()
{
    QStringList headers = {"Name", "Card", "Account", "IBAN", "Balance"};

    QVector<QTableWidget*> tables = {
        ui->tableWidget_2,
        ui->tableWidget,
        ui->tableWidget_3
    };

    for (auto table : tables) {
        table->clear();
        table->setRowCount(0);
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setStretchLastSection(true);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setShowGrid(true);
        table->setWordWrap(false);
        table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        table->setWordWrap(false);
        table->horizontalHeader()->setTextElideMode(Qt::ElideNone);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        table->resizeColumnsToContents();
    }


    auto customers = bankSystem->getCustomers();

    for (int i = 0; i < customers.GetSize(); ++i)
    {
        auto customer = customers[i];
        QString fullName = QString::fromStdString(customer->getFirstName() + " " + customer->getLastName());
        auto accounts = customer->getAccounts();

        for (int j = 0; j < accounts.GetSize(); ++j)
        {
            auto acc = accounts[j];
            QString card = QString::fromStdString(acc->getCardNumber());
            QString account = QString::fromStdString(acc->getAccountNumber());
            QString iban = QString::fromStdString(acc->getIBANnumber());
            QString balance = QString::number(acc->getAccountBalance());

            QString type = QString::fromStdString(acc->AccountType());

            int tabIndex = 0;
            if (type == "Savings Account") tabIndex = 2;
            else if (type == "Checking Account") tabIndex = 1;
            else if (type == "Qarz_al_Hasan Account") tabIndex = 0;

            QTableWidget* table = tables[tabIndex];
            int row = table->rowCount();
            table->insertRow(row);

            QVector<QString> values = { fullName, card, account, iban, balance };
            for (int col = 0; col < values.size(); ++col) {
                QTableWidgetItem* item = new QTableWidgetItem(values[col]);
                item->setToolTip(values[col]);
                item->setForeground(Qt::black);
                item->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, col, item);
            }
        }
    }
}

