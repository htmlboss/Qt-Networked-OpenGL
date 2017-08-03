QT += core gui network widgets

CONFIG += c++1z

linux-g++ {
    QMAKE_CXXFLAGS += -fopenmp -march=native
    QMAKE_LFLAGS +=  -fopenmp -march=native
}

*-msvc2017 {
    QMAKE_CXXFLAGS += -opennmp -EHsc -std:c++latest
}


TARGET = NetworkedOpenGL
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    transform3d.cpp \
    input.cpp \
    camera.cpp \
    player.cpp \
    mainwindow.cpp \
    oglwidget.cpp \
    serverdialog.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    vertex.h \
    transform3d.h \
    cube.h \
    input.h \
    camera.h \
    player.h \
    mainwindow.h \
    oglwidget.h \
    serverdialog.h

RESOURCES += \
    resources.qrc \
    qdarkstyle/style.qrc

DISTFILES += \
    Shaders/basic.vert \
    Shaders/basic.frag

FORMS += \
    mainwindow.ui \
    serverdialog.ui
