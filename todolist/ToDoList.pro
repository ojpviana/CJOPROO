QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT       += json
CONFIG   += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    taskwidget.cpp

HEADERS += \
    mainwindow.h \
    taskwidget.h

FORMS += \
    mainwindow.ui \
    taskwidget.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target
