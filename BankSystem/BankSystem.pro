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
    DASHBOARDS/AdminDashboard.ui \
    DASHBOARDS/CustomerDashboard.ui \
    DASHBOARDS/LoginForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
