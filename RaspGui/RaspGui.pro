#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T12:22:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaspGui
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    nodeCommunication.cpp

HEADERS  += mainview.h \
    nodeCommunication.h

FORMS    += mainview.ui



unix:!macx: LIBS += -lrf24-bcm

unix:!macx: LIBS += -lrf24mesh

unix:!macx: LIBS += -lrf24network
