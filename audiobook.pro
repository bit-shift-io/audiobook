######################################################################
# Automatically generated by qmake (3.1) Sat Mar 31 10:41:04 2018
######################################################################

TEMPLATE = app
TARGET = audiobook

APP_NAME        = "AudioBook"
APP_LOW_NAME    = "audiobook"
APP_AUTHOR      = "Bronson Mathews"
APP_COPYRIGHT = "(C) 2018 $$APP_AUTHOR"
APP_REVERSE_NAME = "io.bitshift.audiobook"

INCLUDEPATH += . /usr/local/include/
QT += widgets multimedia core
#LIBS += -ltag -lz


# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/book.h \
    src/library.h \
    src/librarymodel.h \
    src/mainwindow.h \
    src/player.h \
    src/audioutil.h \
    src/stretchingheader.h

FORMS += src/mainwindow.ui

SOURCES += src/book.cpp \
    src/library.cpp \
    src/librarymodel.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/player.cpp \
    src/audioutil.cpp \
    src/stretchingheader.cpp

RESOURCES += \
    res/resources.qrc
    
# Install all files on Linux. For make install
unix:!mac:!android {
  target.path = $$PREFIX/bin

  desktop_file.files = resources/$${APP_REVERSE_NAME}.desktop
  desktop_file.path = $$quote($$PREFIX/share/applications/)

  appdata.files = resources/$${APP_REVERSE_NAME}.appdata.xml
  appdata.path = $$quote($$PREFIX/share/metainfo/)

  desktop_icon.files = resources/$${APP_REVERSE_NAME}.svg
  desktop_icon.path = $$quote($$PREFIX/share/pixmaps/)

  INSTALLS += target desktop_file desktop_icon appdata
}

android {
  target.path = $$PREFIX

  INSTALLS += target
}

DISTFILES += \
    src/taglib/CMakeLists.txt \
    src/taglib/ape/ape-tag-format.txt \
    src/taglib/mpeg/id3v2/id3v2.2.0.txt \
    src/taglib/mpeg/id3v2/id3v2.3.0.txt \
    src/taglib/mpeg/id3v2/id3v2.4.0-frames.txt \
    src/taglib/mpeg/id3v2/id3v2.4.0-structure.txt \
    src/taglib/taglib_config.h.cmake
