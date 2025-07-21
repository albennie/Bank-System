#include "AdminDashboard.h"
#include "ui_AdminDashboard.h"
#include "QLineEdit"
#include "QMessageBox"
AdminDashboard::AdminDashboard(std::shared_ptr<BankSystem> system, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AdminDashboard), bankSystem(system)
{
    ui->setupUi(this);

    QString fullName = QString::fromStdString(system->getCurrentUser()->getFirstName() + " " +
                                              system->getCurrentUser()->getLastName());
    ui->welcomeLabel->setText("Welcome, " + fullName);

    addNewCustomerPage = new AddNewCustomer(bankSystem, this);
    viewAllCustomersPage = new ViewAllCustomers(bankSystem, this);
    viewSpecificCustomerPage = new ViewSpecificCustomerAccount(bankSystem, this);
    viewAllAccountsPage = new ViewAllBankAccounts(bankSystem, this);
    viewSpecificAccountPage = new ViewSpecificBankAccount(bankSystem, this);
    viewOtherAdminsPage = new ViewOtherAdmins(bankSystem, this);
    addBankAccountoPage = new AddBankAccount(bankSystem, this);
    editCustomerInfoPage = new EditCustomerInfo(bankSystem, this);

    ui->stackedWidget->addWidget(addNewCustomerPage);
    ui->stackedWidget->addWidget(viewAllCustomersPage);
    ui->stackedWidget->addWidget(viewSpecificCustomerPage);
    ui->stackedWidget->addWidget(viewAllAccountsPage);
    ui->stackedWidget->addWidget(viewSpecificAccountPage);
    ui->stackedWidget->addWidget(viewOtherAdminsPage);
    ui->stackedWidget->addWidget(addBankAccountoPage);
    ui->stackedWidget->addWidget(editCustomerInfoPage);

    ui->stackedWidget->setCurrentIndex(0);

    connect(addNewCustomerPage, &AddNewCustomer::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewAllCustomersPage, &ViewAllCustomers::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewSpecificCustomerPage, &ViewSpecificCustomerAccount::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewAllAccountsPage, &ViewAllBankAccounts::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewSpecificAccountPage, &ViewSpecificBankAccount::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewOtherAdminsPage, &ViewOtherAdmins::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(addBankAccountoPage, &AddBankAccount::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(editCustomerInfoPage, &EditCustomerInfo::backToDashboardRequested, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });


    connect(ui->add_new_customer, &QPushButton::clicked, this, [=]() {
        addNewCustomerPage->resetFields();
        ui->stackedWidget->setCurrentWidget(addNewCustomerPage);
    });


    connect(ui->view_all_customers, &QPushButton::clicked, this, [=]() {
        viewAllCustomersPage->displayAllCustomers();
        ui->stackedWidget->setCurrentWidget(viewAllCustomersPage);
    });

    connect(ui->view_specific_customer, &QPushButton::clicked, this, [=]() {
        viewSpecificCustomerPage->resetFields();
        ui->stackedWidget->setCurrentWidget(viewSpecificCustomerPage);
    });

    connect(ui->view_all_bank_accounts, &QPushButton::clicked, this, [=]() {
        viewAllAccountsPage->populateTables();
        ui->stackedWidget->setCurrentWidget(viewAllAccountsPage);
    });

    connect(ui->view_specific_bank_accounts, &QPushButton::clicked, this, [=]() {
        viewSpecificAccountPage->resetFields();
        ui->stackedWidget->setCurrentWidget(viewSpecificAccountPage);
    });

    connect(ui->view_other_admins, &QPushButton::clicked, this, [=]() {
        viewOtherAdminsPage->displayAllAdmins();
        ui->stackedWidget->setCurrentWidget(viewOtherAdminsPage);
    });

    connect(ui->add_bank_account, &QPushButton::clicked, this, [=]() {
        addBankAccountoPage->resetFields();
        ui->stackedWidget->setCurrentWidget(addBankAccountoPage);
    });

    connect(ui->edit_customer_info, &QPushButton::clicked, this, [=]() {
        editCustomerInfoPage->resetFields();
        ui->stackedWidget->setCurrentWidget(editCustomerInfoPage);
    });

}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::on_logoutButton_clicked()
{
    emit logoutRequested();
}

void AdminDashboard::closeEvent(QCloseEvent *event)
{
    emit logoutRequested();
    QMainWindow::closeEvent(event);
}

void AdminDashboard::on_edit_your_info_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Edit Your Info");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLineEdit* usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("New Username");

    QLineEdit* passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("New Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    layout->addWidget(new QLabel("Enter new username:"));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("Enter new password:"));
    layout->addWidget(passwordEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString newUsername = usernameEdit->text();
        QString newPassword = passwordEdit->text();

        if (newUsername.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Username cannot be empty!");
            return;
        }

        auto admins = bankSystem->getAdmins();
        for (int i = 0; i < admins.GetSize(); ++i)
        {
            if (admins[i]->getUsername() == newUsername.toStdString())
            {
                QMessageBox::warning(this, "Error", "Username already taken!");
                return;
            }
        }

        auto currentAdmin = bankSystem->getCurrentUser();
        currentAdmin->setUsername(newUsername.toStdString());
        if (!newPassword.isEmpty())
            currentAdmin->setPassword(newPassword.toStdString());

        QMessageBox::information(this, "Success", "Information updated successfully.");
    }
}

