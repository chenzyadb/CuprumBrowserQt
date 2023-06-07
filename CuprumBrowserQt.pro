QT += core gui
QT += webenginewidgets
QT += widgets

CONFIG += c++17
CONFIG += c11

SOURCES += \
    main.cpp \
    objects/CuSchemeHandler.cpp \
    utils/CuLogger.cpp \
    utils/JsonObject.cpp \
    utils/utils.cpp \
    widgets/CuTabButton.cpp \
    widgets/CuWebView.cpp \
    windows/MainWindow.cpp

HEADERS += \
    objects/CuSchemeHandler.h \
    utils/CuLogger.h \
    utils/JsonObject.h \
    utils/utils.h \
    widgets/CuTabButton.h \
    widgets/CuWebView.h \
    windows/MainWindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = media/cu_icon.ico
VERSION = 1.0.0
QMAKE_TARGET_PRODUCT = CuprumBrowserQt
QMAKE_TARGET_COMPANY = Chenzyadb
QMAKE_TARGET_DESCRIPTION = CuprumBrowserQt Main
QMAKE_TARGET_COPYRIGHT = Copyright (C) Chenzyadb, All Rights Reserved.
