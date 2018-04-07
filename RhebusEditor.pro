#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T14:19:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RhebusEditor
TEMPLATE = app

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        renderarea.cpp \
    definitionmodel.cpp \
    definitionitem.cpp \
    definitionview.cpp \
    shape.cpp \
    triangle.cpp \
    rectangle.cpp \
    line.cpp \
    path.cpp \
    adddefinitionwizard.cpp \
    descriptionitem.cpp \
    rootitem.cpp \
    rootdefinition.cpp \
    descriptionrenderer.cpp

HEADERS += \
        mainwindow.hpp \
        renderarea.hpp \
    definitionmodel.hpp \
    definitionitem.hpp \
    definitionview.hpp \
    shape.hpp \
    triangle.hpp \
    rectangle.hpp \
    line.hpp \
    path.hpp \
    adddefinitionwizard.hpp \
    descriptionitem.hpp \
    rootitem.hpp \
    rootdefinition.hpp \
    descriptionrenderer.hpp

FORMS += \
        mainwindow.ui \
    adddefinitionwizard.ui
