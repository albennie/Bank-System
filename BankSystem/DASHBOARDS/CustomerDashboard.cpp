#include "CustomerDashboard.h"
#include "ui_CustomerDashboard.h"
#include "QMessageBox"
#include "QComboBox"
#include "QLineEdit"

CustomerDashboard::CustomerDashboard(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CustomerDashboard),
    bankSystem(system)
{
    ui->setupUi(this);

    ui->welcomeLabel->setText(
        QString::fromStdString("Welcome, " +
                               system->getCurrentUser()->getFirstName() + " " +
                               system->getCurrentUser()->getLastName()));

    auto viewSpecificAccount = new C_ViewSpecificBankAccount(bankSystem, this);
    auto moneyTransfer = new MoneyTransfer(bankSystem, this);

    ui->stackedWidget->addWidget(viewSpecificAccount);
    ui->stackedWidget->addWidget(moneyTransfer);

    connect(ui->view_specific_account, &QPushButton::clicked, [=]() {
        viewSpecificAccount->ShowBankAccountInfo();
        ui->stackedWidget->setCurrentWidget(viewSpecificAccount);
    });
    connect(ui->money_transfer, &QPushButton::clicked, [=]() {
        moneyTransfer->moneyT();
        ui->stackedWidget->setCurrentWidget(moneyTransfer);
    });
    connect(viewSpecificAccount,&C_ViewSpecificBankAccount::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(moneyTransfer,&MoneyTransfer::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

}

CustomerDashboard::~CustomerDashboard() {
    delete ui;
}

void CustomerDashboard::on_logoutButton_clicked() {
    emit logoutRequested();
    this->close();
}

void CustomerDashboard::closeEvent(QCloseEvent *event) {
    emit logoutRequested();
    QMainWindow::closeEvent(event);
}

void CustomerDashboard::on_change_pin_clicked()
{
    shared_ptr<Customer> currentCustomer = bankSystem->getCurrentCustomer();
    if (!currentCustomer)
    {
        QMessageBox::warning(this, "Error", "No customer logged in.");
        return;
    }

    auto accounts = currentCustomer->getAccounts();
    if (accounts.GetSize() == 0)
    {
        QMessageBox::warning(this, "Error", "No accounts found.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Change PIN");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QComboBox* cardCombo = new QComboBox;
    for (int i = 0; i < accounts.GetSize(); ++i)
    {
        cardCombo->addItem(QString::fromStdString(accounts[i]->getCardNumber()));
    }

    QLineEdit* newPINEdit = new QLineEdit;
    newPINEdit->setPlaceholderText("Enter new PIN");
    newPINEdit->setEchoMode(QLineEdit::Password);

    layout->addWidget(new QLabel("Select card:"));
    layout->addWidget(cardCombo);
    layout->addWidget(new QLabel("New PIN:"));
    layout->addWidget(newPINEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString cardNumber = cardCombo->currentText();
        QString newPIN = newPINEdit->text();

        if (newPIN.length() < 4)
        {
            QMessageBox::warning(this, "Error", "PIN must be at least 4 digits.");
            return;
        }

        bool success = currentCustomer->changePIN(cardNumber.toStdString(), newPIN.toStdString());

        if (success)
        {
            QMessageBox::information(this, "Success", "PIN changed successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to change PIN.");
        }
    }
}

void CustomerDashboard::on_change_static_pass_clicked()
{
    auto currentCustomer = bankSystem->getCurrentCustomer();
    if (!currentCustomer)
    {
        QMessageBox::warning(this, "Error", "No customer logged in.");
        return;
    }

    auto accounts = currentCustomer->getAccounts();
    if (accounts.GetSize() == 0)
    {
        QMessageBox::warning(this, "Error", "No accounts found.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Change Static Second Password");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QComboBox* cardCombo = new QComboBox;
    for (int i = 0; i < accounts.GetSize(); ++i)
    {
        cardCombo->addItem(QString::fromStdString(accounts[i]->getCardNumber()));
    }

    QLineEdit* newPassEdit = new QLineEdit;
    newPassEdit->setPlaceholderText("Enter new static password");
    newPassEdit->setEchoMode(QLineEdit::Password);

    layout->addWidget(new QLabel("Select card:"));
    layout->addWidget(cardCombo);
    layout->addWidget(new QLabel("New Static Password:"));
    layout->addWidget(newPassEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString cardNumber = cardCombo->currentText();
        QString newPass = newPassEdit->text();

        if (newPass.length() < 5)
        {
            QMessageBox::warning(this, "Error", "Password must be at least 5 characters.");
            return;
        }

        bool success = currentCustomer->changeStaticSecondPassword(cardNumber.toStdString(), newPass.toStdString());

        if (success)
        {
            QMessageBox::information(this, "Success", "Static second password changed successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to change password.");
        }
    }
}

void CustomerDashboard::on_change_info_clicked()
{
    auto customer = bankSystem->getCurrentCustomer();
    if (!customer)
    {
        QMessageBox::warning(this, "Error", "No customer is currently logged in.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Change Account Info");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLineEdit* usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("New Username");

    QLineEdit* passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("New Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    layout->addWidget(new QLabel("New Username:"));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("New Password:"));
    layout->addWidget(passwordEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString newUsername = usernameEdit->text().trimmed();
        QString newPassword = passwordEdit->text();

        bool changed = false;

        if (!newUsername.isEmpty())
        {
            auto customers = bankSystem->getCustomers();
            bool duplicate = false;

            for (int i = 0; i < customers.GetSize(); ++i)
            {
                if (customers[i]->getUsername() == newUsername.toStdString())
                {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate)
            {
                QMessageBox::warning(this, "Error", "Username already taken. Try another.");
                return;
            }

            customer->setUsername(newUsername.toStdString());
            changed = true;
        }

        if (!newPassword.isEmpty())
        {
            customer->setPassword(newPassword.toStdString());
            changed = true;
        }

        if (changed)
        {
            QMessageBox::information(this, "Success", "Changes saved successfully.");
        }
        else
        {
            QMessageBox::information(this, "Info", "Nothing was changed.");
        }
    }
}

