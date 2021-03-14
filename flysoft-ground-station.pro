QT       += core gui network mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

DESTDIR = $$PWD/target/$${BUILD_TYPE}
OBJECTS_DIR = $${DESTDIR}/.objects
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

SRC_FOLDER=src
HDR_FOLDER=hdr
FRM_FOLDER=frm
RES_FOLDER=res

SOURCES += \
    configdialog.cpp \
    debugdialog.cpp \
    dronedatapoint.cpp \
    flysoftmqttadapter.cpp \
    main.cpp \
    flysoftgroundstation.cpp

HEADERS += \
    configdialog.h \
    debugdialog.h \
    dronedatapoint.h \
    flysoft_global.h \
    flysoftgroundstation.h \
    flysoftmqttadapter.h

FORMS += \
    config_dialog.ui \
    debugdialog.ui \
    flysoftgroundstation.ui

TRANSLATIONS += \
    flysoft-ground-station_en_CH.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
