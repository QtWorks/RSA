#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T14:17:11
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = RSA
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

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    fonts/FontAwesome5.otf \
    fonts/RobotoCondensed-Bold.ttf \
    fonts/RobotoCondensed-BoldItalic.ttf \
    fonts/RobotoCondensed-Italic.ttf \
    fonts/RobotoCondensed-Light.ttf \
    fonts/RobotoCondensed-LightItalic.ttf \
    fonts/RobotoCondensed-Regular.ttf \
    stylesheets/style.css

HEADERS += \
    src/faicons.h \
    src/mainwindow.h \
    src/rsa.h \
    src/keygenerationdialog.h \
    src/advancedoptionsdialog.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/rsa.cpp \
    src/keygenerationdialog.cpp \
    src/advancedoptionsdialog.cpp
