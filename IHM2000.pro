QT       += core gui sql

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

SOURCES += \
    customObjects/resizablerubberband.cpp \
    explorerablumimages.cpp \
    exploreralbums.cpp \
    explorerb.cpp \
    main.cpp \
    database.cpp \
    mainwindow.cpp \
    models/image.cpp \
    customObjects/graphicsviewzoom.cpp \
    customObjects/clipscene.cpp \
    widgets/explorer.cpp \
    widgets/explorerimg.cpp \
    widgets/info.cpp \
    widgets/resizeimgwidget.cpp \
    widgets/settings.cpp \
    widgets/visionneuse.cpp

HEADERS += \
    customObjects/resizablerubberband.h \
    database.h \
    explorerablumimages.h \
    exploreralbums.h \
    explorerb.h \
    mainwindow.h \
    models/image.h \
    customObjects/graphicsviewzoom.h \
    customObjects/clipscene.h \
    widgets/explorer.h \
    widgets/explorerimg.h \
    widgets/info.h \
    widgets/resizeimgwidget.h \
    widgets/settings.h \
    widgets/visionneuse.h

FORMS += \
    explorerablumimages.ui \
    exploreralbums.ui \
    explorerb.ui \
    mainwindow.ui \
    widgets/explorer.ui \
    widgets/explorerimg.ui \
    widgets/info.ui \
    widgets/resizeimgwidget.ui \
    widgets/settings.ui \
    widgets/visionneuse.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
