#-------------------------------------------------
#
# Project created by QtCreator 2019-03-02T16:13:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_Music_1_0
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    LrcDecoder.cpp

HEADERS += \
        MainWindow.h \
    LrcDecoder.h

FORMS += \
        MainWindowindow.ui

QT += multimedia

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/lib_tinyxml/release/ -ltinyxml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/lib_tinyxml/debug/ -ltinyxml
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/lib/lib_tinyxml/ -ltinyxml

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include/tinyxml
DEPENDPATH += $$PWD/../../../../../../../usr/local/include/tinyxml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/lib_tinyxml/release/libtinyxml.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/lib_tinyxml/debug/libtinyxml.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/lib_tinyxml/release/tinyxml.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/lib_tinyxml/debug/tinyxml.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/lib_tinyxml/libtinyxml.a
