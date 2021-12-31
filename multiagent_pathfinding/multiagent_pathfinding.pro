TEMPLATE = app
TARGET = multiagent_pathfinding

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    addobstacledialog.cpp \
    addrobotdialog.cpp \
    main.cpp \
    mainWindow.cpp \
    obstacle.cpp \
    robot.cpp

HEADERS += \
    addobstacledialog.h \
    addrobotdialog.h \
    mainWindow.h \
    obstacle.h \
    robot.h
