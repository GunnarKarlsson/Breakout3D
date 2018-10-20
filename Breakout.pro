#-------------------------------------------------
#
# Project created by QtCreator 2018-10-20T08:50:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Breakout
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

INCLUDEPATH += \
            "/Users/gunnarkarlsson/git/glm"

SOURCES += \
        main.cpp \
    shader.cpp \
    basicshader.cpp \
    entity.cpp \
    gamewindow.cpp \
    assetmanager.cpp

HEADERS += \
    shader.h \
    basicshader.h \
    entity.h \
    camera.h \
    stb_image.h \
    common.h \
    gamewindow.h \
    assetmanager.h \
    stb_image.h \
    collision.h

FORMS +=

DISTFILES += \
    basic.frag \
    basic.vert \
    font.png \
    minecraft_bricks.png \
    pink.png \
    rainbow.png

RESOURCES += \
    resources.qrc
