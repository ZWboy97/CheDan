#-------------------------------------------------
#
# Project created by QtCreator 2017-09-12T19:33:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CheDan
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        loginwindow.cpp \
    user.cpp \
    mainwindow.cpp \
    questionlistitem.cpp \
    userlistitem.cpp \
    detaildialog.cpp \
    basicinfo.cpp \
    question.cpp \
    answer.cpp \
    answerlistitem.cpp \
    tools.cpp

HEADERS += \
        loginwindow.h \
    user.h \
    mainwindow.h \
    questionlistitem.h \
    userlistitem.h \
    detaildialog.h \
    basicinfo.h \
    question.h \
    answer.h \
    answerlistitem.h \
    tools.h

FORMS += \
        loginwindow.ui \
    mainwindow.ui \
    questionlistitem.ui \
    userlistitem.ui \
    detaildialog.ui \
    answerlistitem.ui \
    userdialog.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    Resource/answerpic.png \
    Resource/fans.png \
    Resource/question.png
