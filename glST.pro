#-------------------------------------------------
#
# Project created by QtCreator 2019-09-04T09:31:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = glST
TEMPLATE = app
include(utils/utils.pri)
include(json/json.pri)
include(glrender/glrender.pri)




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
CONFIG += debug_and_release

win32 {
    DEFINES += _WINDOWS
    DEFINES += WIN32
#opencv
    INCLUDEPATH += $$PWD/3rdparty/opencv/opencv/build/include
    CONFIG(debug, debug|release) {
            LIBS += -L$$PWD/3rdparty/opencv/opencv/build/x64/vc15/lib
        LIBS += -lopencv_world410d

    } else {
        LIBS += -L$$PWD/3rdparty/opencv/opencv/build/x64/vc15/lib
        LIBS +=-lopencv_world410
    }

#ffmpeg
     INCLUDEPATH += $$PWD/3rdparty/ffmpeg/include
     LIBS+=-L$$PWD/3rdparty/ffmpeg/lib/build/x64/vc15/lib

#glm
    INCLUDEPATH += $$PWD/3rdparty/glm


}













SOURCES += \
        main.cpp \
        mainwindow.cpp \
        myopengl.cpp\
        globalinfos.cpp

HEADERS += \
        mainwindow.h \
        myopengl.h\
        globalinfos.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
