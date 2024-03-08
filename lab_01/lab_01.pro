QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawer.cpp \
    errs.cpp \
    figure.cpp \
    linker.cpp \
    linkers.cpp \
    main.cpp \
    mainwindow.cpp \
    point.cpp \
    points.cpp \
    request.cpp

HEADERS += \
    drawer.h \
    errs.h \
    figure.h \
    linker.h \
    linkers.h \
    mainwindow.h \
    point.h \
    points.h \
    request.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
