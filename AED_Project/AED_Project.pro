QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrhythmiadetection.cpp \
    cprfeedback.cpp \
    main.cpp \
    mainwindow.cpp \
    simulatedscenarios.cpp \
    visualprompts.cpp

HEADERS += \
    arrhythmiadetection.h \
    cprfeedback.h \
    mainwindow.h \
    simulatedscenarios.h \
    visualprompts.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3004project.png

RESOURCES += \
    Resources.qrc
