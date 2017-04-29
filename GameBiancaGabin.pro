#-------------------------------------------------
#
# Project created by QtCreator 2017-03-11T14:20:53
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excalibur
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

#RC_ICONS = ressources/chateauAlpha.ico

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
    ressources/grenouille.qrc \
    ressources/poulet.qrc \
    ressources/ours.qrc \
    ressources/cube.qrc \
    ressources/tetegabin.qrc \
    ressources/aie.qrc \
    ressources/drole.qrc \
    ressources/arrete.qrc \
    ressources/souris.qrc \
    ressources/pasmoi.qrc \
    ressources/fleauone.qrc \
    ressources/fleauthreemap.qrc \
    ressources/fleauthree.qrc \
    ressources/fleautwomap.qrc \
    ressources/fleautwo.qrc \
    ressources/fleauonemap.qrc \
    ressources/spritegabinone.qrc \
    ressources/spritegabintwo.qrc \
    ressources/tamaratwo.qrc \
    ressources/tetebiancatwo.qrc \
    ressources/dragonone.qrc \
    ressources/dragontwo.qrc \
    ressources/dragonfour.qrc \
    ressources/dragonthree.qrc

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    plugins/audio/libqtaudio_opensles.so \
    plugins/bearer/libqandroidbearer.so \
    plugins/canbus/libqtpeakcanbus.so \
    plugins/canbus/libqttinycanbus.so \
    plugins/geoservices/libqtgeoservices_esri.so \
    plugins/geoservices/libqtgeoservices_mapbox.so \
    plugins/geoservices/libqtgeoservices_nokia.so \
    plugins/geoservices/libqtgeoservices_osm.so \
    plugins/iconengines/libqsvgicon.so \
    plugins/imageformats/libqgif.so \
    plugins/imageformats/libqicns.so \
    plugins/imageformats/libqico.so \
    plugins/imageformats/libqjpeg.so \
    plugins/imageformats/libqsvg.so \
    plugins/imageformats/libqtga.so \
    plugins/imageformats/libqtiff.so \
    plugins/imageformats/libqwbmp.so \
    plugins/imageformats/libqwebp.so \
    plugins/mediaservice/libqtmedia_android.so \
    plugins/platforms/android/libqtforandroid.so \
    plugins/playlistformats/libqtmultimedia_m3u.so \
    plugins/position/libqtposition_android.so \
    plugins/position/libqtposition_positionpoll.so \
    plugins/qmltooling/libqmldbg_debugger.so \
    plugins/qmltooling/libqmldbg_inspector.so \
    plugins/qmltooling/libqmldbg_local.so \
    plugins/qmltooling/libqmldbg_native.so \
    plugins/qmltooling/libqmldbg_profiler.so \
    plugins/qmltooling/libqmldbg_quickprofiler.so \
    plugins/qmltooling/libqmldbg_server.so \
    plugins/qmltooling/libqmldbg_tcp.so \
    plugins/sceneparsers/libgltfsceneio.so \
    plugins/sensorgestures/libqtsensorgestures_plugin.so \
    plugins/sensorgestures/libqtsensorgestures_shakeplugin.so \
    plugins/sensors/libqtsensors_android.so \
    plugins/sensors/libqtsensors_generic.so \
    plugins/sqldrivers/libqsqlite.so \
    plugins/video/videonode/libqtsgvideonode_android.so \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
