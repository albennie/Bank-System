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
    main.cpp \
    DASHBOARDS\LoginForm.cpp \
    BASECLASSES/LinkedList.cpp \
    BASECLASSES/Node.cpp

HEADERS += \
    DASHBOARDS\LoginForm.h \
    BASECLASSES/LinkedList.h \
    BASECLASSES/Node.h

FORMS += \
    DASHBOARDS\LoginForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
