#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T21:02:31
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerGame
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp\
        Server.cpp \
    XMLClasses\Players.cpp \
    MappingObject.cpp \
    XMLClasses/NamePlayer.cpp \
    XMLClasses/AlertForUser.cpp \
    XMLClasses/RequestNewGame.cpp \
    XMLClasses/AcceptedName.cpp \
    XMLClasses/Fight.cpp \
    XMLClasses/KeyGame.cpp \
    XMLClasses/Position.cpp

HEADERS  += MainWindow.h\
        Server.h \
    XMLClasses\Players.h \
    MappingObject.h \
    XMLClasses/NamePlayer.h \
    XMLClasses/AlertForUser.h \
    XMLClasses/RequestNewGame.h \
    XMLClasses/AcceptedName.h \
    XMLClasses/Fight.h \
    XMLClasses/KeyGame.h \
    XMLClasses/Position.h

FORMS    += MainWindow.ui

CONFIG += c++11
