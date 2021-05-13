QT       += core gui widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    gradientwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    palgenmixwidget.cpp \
    palgenwidget.cpp

HEADERS += \
    gradientwidget.h \
    mainwindow.h \
    palgenmixwidget.h \
    palgenwidget.h \
    segacolors.h

FORMS += \
    mainwindow.ui \
    palgenmixwidget.ui

RESOURCES += \
    main.qrc

DISTFILES += \
    colorpicker.png
