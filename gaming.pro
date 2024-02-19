TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        circularshape.cpp \
        game.cpp \
        main.cpp \
        node.cpp \
        pathfinding.cpp \
        point.cpp \
        polygon.cpp \
        scene.cpp \
        shape.cpp

HEADERS += \
    circularshape.h \
    game.h \
    node.h \
    pathfinding.h \
    point.h \
    polygon.h \
    scene.h \
    shape.h
