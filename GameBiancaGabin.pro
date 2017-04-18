#-------------------------------------------------
#
# Project created by QtCreator 2017-03-11T14:20:53
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameBiancaGabin
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


SOURCES += main.cpp\
        mainwindow.cpp \
    excalibur.cpp \
    gabin.cpp \
    bianca.cpp \
    gabinennemie.cpp \
    biancaennemie.cpp

HEADERS  += mainwindow.h \
    excalibur.h \
    gabin.h \
    bianca.h \
    gabinennemie.h \
    biancaennemie.h

RC_ICONS = ressources/chateauAlpha.ico

RESOURCES += \
    ressources/excaliburfull.qrc \
    ressources/excaliburbiancacontraste.qrc \
    ressources/excaliburgabincontraste.qrc \
    ressources/chateau.qrc \
    ressources/select.qrc \
    ressources/flechehaut.qrc \
    ressources/flechebas.qrc \
    ressources/paysage.qrc \
    ressources/nombianca.qrc \
    ressources/nomgabin.qrc \
    ressources/tetebianca.qrc \
    ressources/spritegabin1.qrc \
    ressources/spritegabin2.qrc \
    ressources/gameover.qrc \
    ressources/espace.qrc \
    ressources/nuage.qrc \
    ressources/radhia.qrc \
    ressources/bernard.qrc \
    ressources/jerome.qrc \
    ressources/tamara.qrc \
    ressources/brice.qrc \
    ressources/carlos.qrc \
    ressources/alex.qrc \
    ressources/kiwi.qrc \
    ressources/doudou.qrc \
    ressources/dragon1.qrc \
    ressources/dragon2.qrc \
    ressources/dragon3.qrc \
    ressources/dragon4.qrc \
    ressources/grenouille.qrc \
    ressources/poulet.qrc \
    ressources/ours.qrc \
    ressources/tamara2.qrc \
    ressources/fleau1.qrc \
    ressources/fleau2.qrc \
    ressources/fleau3.qrc \
    ressources/fleau1map.qrc \
    ressources/fleau2map.qrc \
    ressources/fleau3map.qrc \
    ressources/cube.qrc \
    ressources/tetebianca2.qrc \
    ressources/tetegabin.qrc \
    ressources/aie.qrc \
    ressources/drole.qrc \
    ressources/arrete.qrc \
    ressources/souris.qrc \
    ressources/pasmoi.qrc
