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

macx {
    QMAKE_MAC_SDK = macosx10.13
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    Windows/mainwindow.cpp \
    Windows/adddefinitionwizard.cpp \
    Views/renderarea.cpp \
    Views/descriptionrenderer.cpp \
    Views/definitionview.cpp \
    Models/definitionmodel.cpp \
    Shapes/shape.cpp \
    Shapes/triangle.cpp \
    Shapes/rectangle.cpp \
    Shapes/line.cpp \
    Shapes/path.cpp \
    Items/layeritem.cpp \
    Items/rootitem.cpp \
    Items/descriptionitem.cpp \
    Items/rootdefinitionitem.cpp \
    Items/rootlayeritem.cpp \
    Items/shapeitem.cpp \
    Items/objectitem.cpp \
    Windows/layerdialog.cpp \
    Windows/objectdialog.cpp \
    Windows/programwindow.cpp \
    Views/canvasrenderer.cpp

HEADERS += \
    Windows/mainwindow.hpp \
    Windows/adddefinitionwizard.hpp \
    Views/renderarea.hpp \
    Views/definitionview.hpp \
    Views/descriptionrenderer.hpp \
    Models/definitionmodel.hpp \
    Shapes/shape.hpp \
    Shapes/triangle.hpp \
    Shapes/rectangle.hpp \
    Shapes/line.hpp \
    Shapes/path.hpp \
    Items/descriptionitem.hpp \
    Items/rootitem.hpp \
    Items/layeritem.hpp \
    Items/rootdefinitionitem.hpp \
    Items/rootlayeritem.hpp \
    Items/shapeitem.hpp \
    Items/objectitem.hpp \
    Windows/layerdialog.hpp \
    Windows/objectdialog.hpp \
    Windows/programwindow.hpp \
    Views/canvasrenderer.hpp

FORMS += \
    Windows/mainwindow.ui \
    Windows/adddefinitionwizard.ui \
    Windows/layerdialog.ui \
    Windows/objectdialog.ui \
    Windows/programwindow.ui
