#include "ADMINOPTIONS/AddNewCustomer.h"
#include "ui_AddNewCustomer.h"
#include "QString"
#include "QMessageBox"

AddNewCustomer::AddNewCustomer(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddNewCustomer)
    , bankSystem(system)
{
    ui->setupUi(this);
}

AddNewCustomer::~AddNewCustomer()
{
    delete ui;
}

void AddNewCustomer::on_logoutButton_clicked()
{
    emit backToDashboardRequested();
}


void AddNewCustomer::on_Add_btn_clicked()
{
    QString Fname = ui->Fname_LineEdit->text();
    QString Lname = ui->LName_LineEdit->text();
    QString ID = ui->ID_LineEdit->text();
    QString username = ui->Username_LineEdit->text();
    QString password = ui->Password_LineEdit->text();
    QString day = ui->Day_SpinBox->text();
    QString month = ui->Month_SpinBox->text();
    QString year = ui->Year_SpinBox->text();

    if(Fname == nullptr ||
        Lname == nullptr ||
        ID == nullptr ||
        username == nullptr ||
        password == nullptr)
    {
        QMessageBox::warning(this,"Error","All fields must be full!");
    }
    else if(ui->comboBox->currentText() == "Admin")
    {
        if(bankSystem->addAdmin(Fname.toStdString(),
                              Lname.toStdString(),
                              ID.toStdString(),
                              username.toStdString(),
                              password.toStdString(),
                              day.toInt(),
                              month.toInt(),
                                 year.toInt()) && (bankSystem->getCurrentUser()->getUsername() == "admin"))
        {
            auto box = new QMessageBox(this);
            box->setWindowTitle("Added Successfully");
            box->setText("Admin Added Successfully!");
            box->setIcon(QMessageBox::Information);
            box->addButton(QMessageBox::Ok);

            connect(box, &QMessageBox::accepted, this, [=]() {
                emit backToDashboardRequested();
                box->deleteLater();
            });

            box->exec();
        }
        else
        {
            if(!(bankSystem->getCurrentUser()->getUsername() == "admin"))
            {
                QMessageBox::warning(this,"Error","You don't have permission to add admins!");
            }
            else if(!bankSystem->addAdmin(Fname.toStdString(),
                                      Lname.toStdString(),
                                      ID.toStdString(),
                                      username.toStdString(),
                                      password.toStdString(),
                                      day.toInt(),
                                      month.toInt(),
                                      year.toInt()))
            {
                QMessageBox::warning(this,"Error","Try another username!");
            }
        }
    }
    else
    {
        if(bankSystem->addCustomer(Fname.toStdString(),
                                 Lname.toStdString(),
                                 ID.toStdString(),
                                 username.toStdString(),
                                 password.toStdString(),
                                 day.toInt(),
                                 month.toInt(),
                                 year.toInt()))
        {
            auto box = new QMessageBox(this);
            box->setWindowTitle("Added Successfully");
            box->setText("Customer Added Successfully!");
            box->setIcon(QMessageBox::Information);
            box->addButton(QMessageBox::Ok);

            connect(box, &QMessageBox::accepted, this, [=]() {
                emit backToDashboardRequested();
                box->deleteLater();
            });

            box->exec();        }
        else
        {
            QMessageBox::warning(this,"Error","Try another username!");
        }
    }
}

void AddNewCustomer::resetFields() {
    ui->Fname_LineEdit->clear();
    ui->LName_LineEdit->clear();
    ui->ID_LineEdit->clear();
    ui->Username_LineEdit->clear();
    ui->Password_LineEdit->clear();
    ui->Day_SpinBox->setValue(1);
    ui->Month_SpinBox->setValue(1);
    ui->Year_SpinBox->setValue(1300);
    ui->comboBox->setCurrentIndex(0);
}
