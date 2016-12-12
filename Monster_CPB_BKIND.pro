TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra
SOURCES += main.cpp \
    Evenements.cc \
    Niveaux.cc \
    Affichage.cc \
    Mouvement.cc \
    Initialisation.cc \
    Score.cc

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf

INCLUDEPATH+=-I/usr/include/SDL/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Evenements.h \
    Niveaux.h \
    Affichage.h \
    Mouvement.h \
    Initialisation.h \
    Score.h
