#-------------------------------------------------
#
# Project created by QtCreator 2020-02-11T10:45:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        gameobject.cpp \
        hierarchy.cpp \
        inspector.cpp \
        main.cpp \
        mainwindow.cpp \
        scenewidget.cpp

HEADERS += \
        gameobject.h \
        hierarchy.h \
        inspector.h \
        mainwindow.h \
        scenewidget.h

FORMS += \
        color.ui \
        hierarchy.ui \
        mainwindow.ui \
        shape.ui \
        size.ui \
        stroke.ui \
        transform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    icons/engine/engineTools.qrc \
    themes/qdarkstyle/style.qrc

DISTFILES += \
    icons/engine/rotateTool.png \
    icons/engine/scaleTool.png
