QT       += core gui
QT       += core gui sql
QT += core gui network
QT       += charts serialport multimedia multimediawidgets widgets printsupport network axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
TARGET = mail
TARGET = Atelier_Connexion
CONFIG += c++11 Console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    biens.cpp \
    client.cpp \
    connection.cpp \
    contrat.cpp \
    employe.cpp \
    excel.cpp \
    histrorique.cpp \
    login.cpp \
    login_bd.cpp \
    main.cpp \
    mainwindow.cpp \
    smtp.cpp \
    statistique.cpp

HEADERS += \
    arduino.h \
    biens.h \
    client.h \
    connection.h \
    contrat.h \
    employe.h \
    excel.h \
    histrorique.h \
    login.h \
    login_bd.h \
    mainwindow.h \
    smtp.h \
    statistique.h

FORMS += \
    login.ui \
    mainwindow.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

