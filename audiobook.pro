TEMPLATE = app

QT += charts qml quick svg 
QT += widgets multimedia core
#LIBS += -ltag -lz

android: {
    QT += androidextras
#    include(3rdparty/kirigami/kirigami.pri)
}

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



HEADERS += \
  src/book.h \
  src/library.h \
  src/librarymodel.h \
  src/player.h \
  src/settings.h \
  src/util.h

SOURCES += \
  src/book.cpp \
  src/library.cpp \
  src/librarymodel.cpp \
  src/main.cpp \
  src/player.cpp \
  src/settings.cpp \
  src/util.cpp

RESOURCES += \
  res/res.qrc \
  src/qml.qrc
    
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
DISTFILES += \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
}
