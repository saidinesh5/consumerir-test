TEMPLATE = app

QT += core

CONFIG += c++11

SOURCES += main.cpp

CONFIG += link_pkgconfig
PKGCONFIG += android-headers libhardware

target.path = $$(PREFIX)/usr/bin

INSTALLS += target
