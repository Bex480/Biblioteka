QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    helpwindow.cpp \
    izmjena.cpp \
    izmjenaknjiga.cpp \
    izmjenarazreda.cpp \
    izmjenazanra.cpp \
    knjiga.cpp \
    main.cpp \
    mainwindow.cpp \
    novagodina.cpp \
    novirazred.cpp \
    novizanr.cpp \
    ucenik.cpp \
    uvod.cpp

HEADERS += \
    helpwindow.h \
    izmjena.h \
    izmjenaknjiga.h \
    izmjenarazreda.h \
    izmjenazanra.h \
    knjiga.h \
    mainwindow.h \
    novagodina.h \
    novirazred.h \
    novizanr.h \
    ucenik.h \
    uvod.h

FORMS += \
    helpwindow.ui \
    izmjena.ui \
    izmjenaknjiga.ui \
    izmjenarazreda.ui \
    izmjenazanra.ui \
    knjiga.ui \
    mainwindow.ui \
    novagodina.ui \
    novirazred.ui \
    novizanr.ui \
    ucenik.ui \
    uvod.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc

DISTFILES += \
    ../../../../Nova fascikla/Screenshot_1171.png
