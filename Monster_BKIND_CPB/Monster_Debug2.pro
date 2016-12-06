TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra
SOURCES += main.cpp \
    Evenements.cc \
    Fonctions.cc \
    Structures.cc \
    Niveaux.cc \
    Affichage.cc

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf

INCLUDEPATH+=-I/usr/include/SDL/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Evenements.h \
    Fonctions.h \
    Structures.h \
    Niveaux.h \
    Affichage.h

