#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T22:51:14
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RpgGame
TEMPLATE = app


SOURCES += main.cpp\
    Client/Client.cpp \
    ../ServerGame/XMLClasses/NamePlayer.cpp \
    ../ServerGame/XMLClasses/Players.cpp \
    ../ServerGame/XMLClasses/RequestNewGame.cpp \
    ../ServerGame/MappingObject.cpp \
    ../ServerGame/XMLClasses/AlertForUser.cpp \
    ../ServerGame/XMLClasses/AcceptedName.cpp \
    ../ServerGame/XMLClasses/Fight.cpp \
    Gui/Views/ActorGraphicsItem.cpp \
    Gui/Views/GraphicsViewGame.cpp \
    ParserMap/TmxMap.cpp \
    Gui/Forms/FrmCommunicationPlayer.cpp \
    Gui/Forms/MainWindow.cpp \
    ../ServerGame/XMLClasses/KeyGame.cpp \
    Gui/Views/MageGraphicItem.cpp \
    CollisionAlgo.cpp \
    Gui/Views/NinjaGraphicItem.cpp \
    Gui/Views/KnightGraphicItem.cpp \
    Gui/Views/ShunLiGraphicItem.cpp \
    Automaton/Struture/FinalState.cpp \
    Automaton/Struture/Relationship.cpp \
    Automaton/Struture/State.cpp \
    Automaton/AF.cpp \
    Automaton/AFD.cpp \
    ../ServerGame/XMLClasses/Position.cpp \
    Gui/Forms/FrmSetting.cpp \
    Compilador/Parser.cpp \
    Compilador/Scanner.cpp \
    Compilador/Token.cpp \
    Grammar/GrammarElement.cpp \
    Grammar/GrammarLL.cpp \
    Grammar/Production.cpp \
    Compilador/Interpreter.cpp \
    Gui/Forms/FrmSelectPlayer.cpp

HEADERS  += ../ServerGame/XMLClasses/NamePlayer.h \
    ../ServerGame/XMLClasses/Players.h \
    ../ServerGame/XMLClasses/RequestNewGame.h \
    ../ServerGame/MappingObject.h \
    ../ServerGame/XMLClasses/AlertForUser.h \
    ../ServerGame/XMLClasses/AcceptedName.h \
    ../ServerGame/XMLClasses/Fight.h \
    Gui/Forms/FrmCommunicationPlayer.h \
    Gui/Forms/MainWindow.h \
    Gui/Views/ActorGraphicsItem.h \
    Gui/Views/GraphicsViewGame.h \
    ParserMap/RapidXML/rapidxml.hpp \
    ParserMap/RapidXML/rapidxml_iterators.hpp \
    ParserMap/RapidXML/rapidxml_print.hpp \
    ParserMap/RapidXML/rapidxml_utils.hpp \
    ParserMap/TmxMap.h \
    Client/Client.h \
    ../ServerGame/XMLClasses/KeyGame.h \
    Gui/Views/MageGraphicItem.h \
    CollisionAlgo.h \
    Gui/Views/NinjaGraphicItem.h \
    Gui/Views/KnightGraphicItem.h \
    Gui/Views/ShunLiGraphicItem.h \
    Automaton/Struture/FinalState.h \
    Automaton/Struture/Relationship.h \
    Automaton/Struture/State.h \
    Automaton/AF.h \
    Automaton/AFD.h \
    ../ServerGame/XMLClasses/Position.h \
    Gui/Forms/FrmSetting.h \
    Compilador/Enums.h \
    Compilador/Parser.h \
    Compilador/Scanner.h \
    Compilador/Token.h \
    Grammar/GrammarElement.h \
    Grammar/GrammarLL.h \
    Grammar/Production.h \
    Util/GeneralFunctions.h \
    Compilador/Interpreter.h \
    Gui/Forms/FrmSelectPlayer.h

FORMS    += Gui/Forms/FrmCommunicationPlayer.ui \
    Gui/Forms/MainWindow.ui \
    Gui/Forms/FrmSetting.ui \
    Gui/Forms/FrmSelectPlayer.ui

CONFIG += c++11

RESOURCES += \
    rs.qrc

OTHER_FILES +=
