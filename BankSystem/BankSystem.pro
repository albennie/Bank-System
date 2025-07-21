QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/BASECLASSES
INCLUDEPATH += $$PWD/DASHBOARDS
INCLUDEPATH += $$PWD/ADMINOPTIONS
INCLUDEPATH += $$PWD/CUSTOMEROPTIONS

SOURCES += \
    ADMINOPTIONS/AddBankAccount.cpp \
    ADMINOPTIONS/AddNewCustomer.cpp \
    ADMINOPTIONS/EditCustomerInfo.cpp \
    ADMINOPTIONS/ViewAllBankAccounts.cpp \
    ADMINOPTIONS/ViewAllCustomers.cpp \
    ADMINOPTIONS/ViewOtherAdmins.cpp \
    ADMINOPTIONS/ViewSpecificBankAccount.cpp \
    ADMINOPTIONS/ViewSpecificCustomerAccount.cpp \
    CUSTOMEROPTIONS/C_ViewSpecificBankAccount.cpp \
    CUSTOMEROPTIONS/MoneyTransfer.cpp \
    DASHBOARDS/AdminDashboard.cpp \
    DASHBOARDS/CustomerDashboard.cpp \
    main.cpp \
    DASHBOARDS\LoginForm.cpp \
    BASECLASSES/LinkedList.cpp \
    BASECLASSES/Node.cpp \
    BASECLASSES/User.cpp \
    BASECLASSES/BankAccount.cpp \
    BASECLASSES/CheckingAccount.cpp \
    BASECLASSES/Qarz_al_HasanAccount.cpp \
    BASECLASSES/SavingsAccount.cpp \
    BASECLASSES/Costomer.cpp \
    BASECLASSES/Admin.cpp \
    BASECLASSES/BankSystem.cpp \
    BASECLASSES/Admin.cpp

HEADERS += \
    ADMINOPTIONS/AddBankAccount.h \
    ADMINOPTIONS/AddNewCustomer.h \
    ADMINOPTIONS/EditCustomerInfo.h \
    ADMINOPTIONS/ViewAllBankAccounts.h \
    ADMINOPTIONS/ViewAllCustomers.h \
    ADMINOPTIONS/ViewOtherAdmins.h \
    ADMINOPTIONS/ViewSpecificBankAccount.h \
    ADMINOPTIONS/ViewSpecificCustomerAccount.h \
    CUSTOMEROPTIONS/C_ViewSpecificBankAccount.h \
    CUSTOMEROPTIONS/MoneyTransfer.h \
    DASHBOARDS/AdminDashboard.h \
    DASHBOARDS/CustomerDashboard.h \
    DASHBOARDS/LoginForm.h \
    BASECLASSES/LinkedList.h \
    BASECLASSES/Node.h \
    BASECLASSES/User.h \
    BASECLASSES/BankAccount.h \
    BASECLASSES/CheckingAccount.h \
    BASECLASSES/Qarz_al_HasanAccount.h \
    BASECLASSES/SavingsAccount.h \
    BASECLASSES/Costomer.h \
    BASECLASSES/Admin.h \
    BASECLASSES/BankSystem.h \
    BASECLASSES/Admin.h

FORMS += \
    ADMINOPTIONS/AddBankAccount.ui \
    ADMINOPTIONS/AddNewCustomer.ui \
    ADMINOPTIONS/EditCustomerInfo.ui \
    ADMINOPTIONS/ViewAllBankAccounts.ui \
    ADMINOPTIONS/ViewAllCustomers.ui \
    ADMINOPTIONS/ViewOtherAdmins.ui \
    ADMINOPTIONS/ViewSpecificBankAccount.ui \
    ADMINOPTIONS/ViewSpecificCustomerAccount.ui \
    CUSTOMEROPTIONS/C_ViewSpecificBankAccount.ui \
    CUSTOMEROPTIONS/MoneyTransfer.ui \
    DASHBOARDS/AdminDashboard.ui \
    DASHBOARDS/CustomerDashboard.ui \
    DASHBOARDS/LoginForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
