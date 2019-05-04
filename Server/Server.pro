TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../lib/sockaddr.cpp \
        ../lib/socket.cpp \
        main.cpp

HEADERS += \
    ../lib/sockaddr.h \
    ../lib/socket.h
