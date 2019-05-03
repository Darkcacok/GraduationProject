TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        sockaddr.cpp \
        socket.cpp

HEADERS += \
    sockaddr.h \
    socket.h
