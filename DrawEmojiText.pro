#-------------------------------------------------
#
# Project created by QtCreator 2018-08-31T10:33:30
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Test
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    MyCentralWidget.cpp \
    DrawEmojiText.cpp

HEADERS += \
        MainWindow.h \
    MyCentralWidget.h \
    DrawEmojiText.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
