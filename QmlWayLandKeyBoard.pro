QT          = core gui-private quick widgets

TEMPLATE    = lib
TARGET      = QmlWestonInputContextPlugin

HEADERS     += \
            qmlwestonplatforminputcontextplugin.h \
            qmlwestonplatforminputcontext.h

SOURCES     += \
            qmlwestonplatforminputcontextplugin.cpp \
            qmlwestonplatforminputcontext.cpp

unix{
    DESTDIR     = $$PWD/build/bin/platforminputcontexts

    MOC_DIR     = $$PWD/build/plugin/moc
    RCC_DIR     = $$PWD/build/plugin/res
    UI_DIR      = $$PWD/build/plugin/ui
    OBJECTS_DIR = $$PWD/build/plugin/obj
}

RESOURCES += \
    res.qrc
