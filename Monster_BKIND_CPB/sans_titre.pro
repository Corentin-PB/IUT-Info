TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf

INCLUDEPATH+=-I/usr/include/SDL/

include(deployment.pri)
qtcAddDeployment()
