#-------------------------------------------------
#
# Project created by QtCreator 2019-07-16T16:46:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = analyser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        constantstools.cpp \
        dbconnector.cpp \
        language.cpp \
        logger.cpp \
        main.cpp \
        mainwindow.cpp \
    analyser.cpp \
<<<<<<< HEAD
    analyserutils.cpp \
    shellhandler.cpp

HEADERS += \
        constantstools.h \
        dbconnector.h \
        language.h \
        logger.h \
        mainwindow.h\
        analyser.h \
        service.h \
        analyserutils.h \
        shellhandler.h

=======
    shellhandler.cpp

HEADERS += \
    mainwindow.h \
    analyser.h \
    service.h \
    shellhandler.h \
    constantstools.h\
    language.h
>>>>>>> e771d9d37b23cf959527305b11bd664c2a353da7
FORMS += \
    mainwindow.ui
