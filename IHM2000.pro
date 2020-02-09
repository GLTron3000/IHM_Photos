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
    explorerablumimages.cpp \
    exploreralbums.cpp \
    explorer.cpp \
    models/imageswitcher.cpp \
    stardelegate.cpp \
    stareditor.cpp \
    starrating.cpp \
    visionneuse.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    models/image.cpp \
    widgets/note.cpp \
    widgets/resizablerubberband.cpp \
    widgets/graphicsviewzoom.cpp \
    widgets/explorerimg.cpp \
    widgets/info.cpp \
    widgets/resizeimgwidget.cpp \
    widgets/settings.cpp


HEADERS += \
    database.h \
    explorerablumimages.h \
    exploreralbums.h \
    explorer.h \
    models/imageswitcher.h \
    mainwindow.h \
    models/image.h \
    stardelegate.h \
    stareditor.h \
    starrating.h \
    widgets/graphicsviewzoom.h \
    widgets/explorerimg.h \
    widgets/info.h \
    widgets/note.h \
    widgets/resizeimgwidget.h \
    widgets/settings.h \
    widgets/resizablerubberband.h \
    visionneuse.h

FORMS += \
    explorerablumimages.ui \
    exploreralbums.ui \
    explorer.ui \
    mainwindow.ui \
    widgets/explorerimg.ui \
    widgets/info.ui \
    widgets/note.ui \
    widgets/resizeimgwidget.ui \
    widgets/settings.ui \
    visionneuse.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
