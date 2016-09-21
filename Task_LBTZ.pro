#-------------------------------------------------
#
# Project created by QtCreator 2016-09-02T10:38:12
#
#-------------------------------------------------

QT       += core gui sql axcontainer
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Task_LBTZ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    employee.cpp \
    excelmodule.cpp \
    wordmodule.cpp \
    AbstractFileModule.cpp

HEADERS  += mainwindow.h \
    database.h \
    employee.h \
    excelmodule.h \
    wordmodule.h \
    AbstractFileModule.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresourse.qrc
