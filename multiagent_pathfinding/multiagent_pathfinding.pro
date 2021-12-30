TEMPLATE = app
TARGET = multiagent_pathfinding

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainWindow.cpp \
    obstacle.cpp \
    robot.cpp

HEADERS += \
    mainWindow.h \
    obstacle.h \
    robot.h
