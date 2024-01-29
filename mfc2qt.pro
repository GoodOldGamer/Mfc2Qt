TEMPLATE = app
TARGET = mfc2qt

QT        += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG    += qt thread

HEADERS  += src/mainwindow.h \
            src/rcscanner.h \
            src/rcwriter.h \
            src/ressourcedef.h \
    src/objectdata.h \
    src/rcrawdata.h \
    src/resourcedata.h \
    src/dialogpreview.h \
    src/dialoglistmodel.h \
    src/dialoglistdelegate.h \
    src/ctrldefinitions.h

SOURCES  += src/main.cpp \
            src/mainwindow.cpp \
            src/rcscanner.cpp \
            src/rcwriter.cpp \
    src/objectdata.cpp \
    src/dialogpreview.cpp \
    src/dialoglistmodel.cpp \
    src/dialoglistdelegate.cpp \
    src/ctrldefinitions.cpp

FORMS    += src/mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
            src/ressources.qrc

DISTFILES += \
            src/makefile \
            src/remove.h.moc
