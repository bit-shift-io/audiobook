TEMPLATE = app

QT += widgets multimedia core sql charts qml quick svg

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

INCLUDEPATH += \
    src/taglib \
    src/taglib/utf8-cpp \
    src/taglib/toolkit \
    src/taglib/mpeg/id3v1 \
    src/taglib/mpeg/id3v2 \
    src/taglib/mpeg/id3v2/frames \
    src/taglib/ape \
    src/taglib/asf \
    src/taglib/flac \
    src/taglib/mp4 \
    src/taglib/mpc \
    src/taglib/mpeg \
    src/taglib/ogg \
    src/taglib/riff \
    src/taglib/trueaudio \
    src/taglib/wavpack \
    src/taglib/ogg/flac \
    src/taglib/ogg/speex \
    src/taglib/ogg/vorbis \
    src/taglib/ogg/opus \
    src/taglib/riff/aiff \
    src/taglib/riff/wav \
    src/taglib/mod \
    src/taglib/it \
    src/taglib/s3m \
    src/taglib/xm

HEADERS += \
  src/book.h \
  src/chapter.h \
  src/chaptermodel.h \
  src/database.h \
  src/libraryfilterproxy.h \
  src/librarymodel.h \
  src/player.h \
  src/settings.h \
  src/taglib/ape/apefile.h \
  src/taglib/ape/apefooter.h \
  src/taglib/ape/apeitem.h \
  src/taglib/ape/apeproperties.h \
  src/taglib/ape/apetag.h \
  src/taglib/asf/asfattribute.h \
  src/taglib/asf/asffile.h \
  src/taglib/asf/asfpicture.h \
  src/taglib/asf/asfproperties.h \
  src/taglib/asf/asftag.h \
  src/taglib/asf/asfutils.h \
  src/taglib/audioproperties.h \
  src/taglib/fileref.h \
  src/taglib/flac/flacfile.h \
  src/taglib/flac/flacmetadatablock.h \
  src/taglib/flac/flacpicture.h \
  src/taglib/flac/flacproperties.h \
  src/taglib/flac/flacunknownmetadatablock.h \
  src/taglib/it/itfile.h \
  src/taglib/it/itproperties.h \
  src/taglib/mod/modfile.h \
  src/taglib/mod/modfilebase.h \
  src/taglib/mod/modfileprivate.h \
  src/taglib/mod/modproperties.h \
  src/taglib/mod/modtag.h \
  src/taglib/mp4/mp4atom.h \
  src/taglib/mp4/mp4coverart.h \
  src/taglib/mp4/mp4file.h \
  src/taglib/mp4/mp4item.h \
  src/taglib/mp4/mp4properties.h \
  src/taglib/mp4/mp4tag.h \
  src/taglib/mpc/mpcfile.h \
  src/taglib/mpc/mpcproperties.h \
  src/taglib/mpeg/id3v1/id3v1genres.h \
  src/taglib/mpeg/id3v1/id3v1tag.h \
  src/taglib/mpeg/id3v2/frames/attachedpictureframe.h \
  src/taglib/mpeg/id3v2/frames/chapterframe.h \
  src/taglib/mpeg/id3v2/frames/commentsframe.h \
  src/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h \
  src/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h \
  src/taglib/mpeg/id3v2/frames/ownershipframe.h \
  src/taglib/mpeg/id3v2/frames/podcastframe.h \
  src/taglib/mpeg/id3v2/frames/popularimeterframe.h \
  src/taglib/mpeg/id3v2/frames/privateframe.h \
  src/taglib/mpeg/id3v2/frames/relativevolumeframe.h \
  src/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h \
  src/taglib/mpeg/id3v2/frames/tableofcontentsframe.h \
  src/taglib/mpeg/id3v2/frames/textidentificationframe.h \
  src/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h \
  src/taglib/mpeg/id3v2/frames/unknownframe.h \
  src/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h \
  src/taglib/mpeg/id3v2/frames/urllinkframe.h \
  src/taglib/mpeg/id3v2/id3v2.h \
  src/taglib/mpeg/id3v2/id3v2extendedheader.h \
  src/taglib/mpeg/id3v2/id3v2footer.h \
  src/taglib/mpeg/id3v2/id3v2frame.h \
  src/taglib/mpeg/id3v2/id3v2framefactory.h \
  src/taglib/mpeg/id3v2/id3v2header.h \
  src/taglib/mpeg/id3v2/id3v2synchdata.h \
  src/taglib/mpeg/id3v2/id3v2tag.h \
  src/taglib/mpeg/mpegfile.h \
  src/taglib/mpeg/mpegheader.h \
  src/taglib/mpeg/mpegproperties.h \
  src/taglib/mpeg/mpegutils.h \
  src/taglib/mpeg/xingheader.h \
  src/taglib/ogg/flac/oggflacfile.h \
  src/taglib/ogg/oggfile.h \
  src/taglib/ogg/oggpage.h \
  src/taglib/ogg/oggpageheader.h \
  src/taglib/ogg/opus/opusfile.h \
  src/taglib/ogg/opus/opusproperties.h \
  src/taglib/ogg/speex/speexfile.h \
  src/taglib/ogg/speex/speexproperties.h \
  src/taglib/ogg/vorbis/vorbisfile.h \
  src/taglib/ogg/vorbis/vorbisproperties.h \
  src/taglib/ogg/xiphcomment.h \
  src/taglib/riff/aiff/aifffile.h \
  src/taglib/riff/aiff/aiffproperties.h \
  src/taglib/riff/rifffile.h \
  src/taglib/riff/riffutils.h \
  src/taglib/riff/wav/infotag.h \
  src/taglib/riff/wav/wavfile.h \
  src/taglib/riff/wav/wavproperties.h \
  src/taglib/s3m/s3mfile.h \
  src/taglib/s3m/s3mproperties.h \
  src/taglib/tag.h \
  src/taglib/taglib_export.h \
  src/taglib/tagunion.h \
  src/taglib/tagutils.h \
  src/taglib/toolkit/taglib.h \
  src/taglib/toolkit/taglib_config.h \
  src/taglib/toolkit/tbytevector.h \
  src/taglib/toolkit/tbytevectorlist.h \
  src/taglib/toolkit/tbytevectorstream.h \
  src/taglib/toolkit/tdebug.h \
  src/taglib/toolkit/tdebuglistener.h \
  src/taglib/toolkit/tfile.h \
  src/taglib/toolkit/tfilestream.h \
  src/taglib/toolkit/tiostream.h \
  src/taglib/toolkit/tlist.h \
  src/taglib/toolkit/tlist.tcc \
  src/taglib/toolkit/tmap.h \
  src/taglib/toolkit/tmap.tcc \
  src/taglib/toolkit/tpropertymap.h \
  src/taglib/toolkit/trefcounter.h \
  src/taglib/toolkit/tstring.h \
  src/taglib/toolkit/tstringlist.h \
  src/taglib/toolkit/tutils.h \
  src/taglib/toolkit/tzlib.h \
  src/taglib/trueaudio/trueaudiofile.h \
  src/taglib/trueaudio/trueaudioproperties.h \
  src/taglib/utf8-cpp/checked.h \
  src/taglib/utf8-cpp/core.h \
  src/taglib/wavpack/wavpackfile.h \
  src/taglib/wavpack/wavpackproperties.h \
  src/taglib/xm/xmfile.h \
  src/taglib/xm/xmproperties.h \
  src/util.h

SOURCES += \
  src/chaptermodel.cpp \
  src/database.cpp \
  src/libraryfilterproxy.cpp \
  src/librarymodel.cpp \
  src/main.cpp \
  src/player.cpp \
  src/settings.cpp \
  src/taglib/ape/apefile.cpp \
  src/taglib/ape/apefooter.cpp \
  src/taglib/ape/apeitem.cpp \
  src/taglib/ape/apeproperties.cpp \
  src/taglib/ape/apetag.cpp \
  src/taglib/asf/asfattribute.cpp \
  src/taglib/asf/asffile.cpp \
  src/taglib/asf/asfpicture.cpp \
  src/taglib/asf/asfproperties.cpp \
  src/taglib/asf/asftag.cpp \
  src/taglib/audioproperties.cpp \
  src/taglib/fileref.cpp \
  src/taglib/flac/flacfile.cpp \
  src/taglib/flac/flacmetadatablock.cpp \
  src/taglib/flac/flacpicture.cpp \
  src/taglib/flac/flacproperties.cpp \
  src/taglib/flac/flacunknownmetadatablock.cpp \
  src/taglib/it/itfile.cpp \
  src/taglib/it/itproperties.cpp \
  src/taglib/mod/modfile.cpp \
  src/taglib/mod/modfilebase.cpp \
  src/taglib/mod/modproperties.cpp \
  src/taglib/mod/modtag.cpp \
  src/taglib/mp4/mp4atom.cpp \
  src/taglib/mp4/mp4coverart.cpp \
  src/taglib/mp4/mp4file.cpp \
  src/taglib/mp4/mp4item.cpp \
  src/taglib/mp4/mp4properties.cpp \
  src/taglib/mp4/mp4tag.cpp \
  src/taglib/mpc/mpcfile.cpp \
  src/taglib/mpc/mpcproperties.cpp \
  src/taglib/mpeg/id3v1/id3v1genres.cpp \
  src/taglib/mpeg/id3v1/id3v1tag.cpp \
  src/taglib/mpeg/id3v2/frames/attachedpictureframe.cpp \
  src/taglib/mpeg/id3v2/frames/chapterframe.cpp \
  src/taglib/mpeg/id3v2/frames/commentsframe.cpp \
  src/taglib/mpeg/id3v2/frames/eventtimingcodesframe.cpp \
  src/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp \
  src/taglib/mpeg/id3v2/frames/ownershipframe.cpp \
  src/taglib/mpeg/id3v2/frames/podcastframe.cpp \
  src/taglib/mpeg/id3v2/frames/popularimeterframe.cpp \
  src/taglib/mpeg/id3v2/frames/privateframe.cpp \
  src/taglib/mpeg/id3v2/frames/relativevolumeframe.cpp \
  src/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.cpp \
  src/taglib/mpeg/id3v2/frames/tableofcontentsframe.cpp \
  src/taglib/mpeg/id3v2/frames/textidentificationframe.cpp \
  src/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.cpp \
  src/taglib/mpeg/id3v2/frames/unknownframe.cpp \
  src/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp \
  src/taglib/mpeg/id3v2/frames/urllinkframe.cpp \
  src/taglib/mpeg/id3v2/id3v2extendedheader.cpp \
  src/taglib/mpeg/id3v2/id3v2footer.cpp \
  src/taglib/mpeg/id3v2/id3v2frame.cpp \
  src/taglib/mpeg/id3v2/id3v2framefactory.cpp \
  src/taglib/mpeg/id3v2/id3v2header.cpp \
  src/taglib/mpeg/id3v2/id3v2synchdata.cpp \
  src/taglib/mpeg/id3v2/id3v2tag.cpp \
  src/taglib/mpeg/mpegfile.cpp \
  src/taglib/mpeg/mpegheader.cpp \
  src/taglib/mpeg/mpegproperties.cpp \
  src/taglib/mpeg/xingheader.cpp \
  src/taglib/ogg/flac/oggflacfile.cpp \
  src/taglib/ogg/oggfile.cpp \
  src/taglib/ogg/oggpage.cpp \
  src/taglib/ogg/oggpageheader.cpp \
  src/taglib/ogg/opus/opusfile.cpp \
  src/taglib/ogg/opus/opusproperties.cpp \
  src/taglib/ogg/speex/speexfile.cpp \
  src/taglib/ogg/speex/speexproperties.cpp \
  src/taglib/ogg/vorbis/vorbisfile.cpp \
  src/taglib/ogg/vorbis/vorbisproperties.cpp \
  src/taglib/ogg/xiphcomment.cpp \
  src/taglib/riff/aiff/aifffile.cpp \
  src/taglib/riff/aiff/aiffproperties.cpp \
  src/taglib/riff/rifffile.cpp \
  src/taglib/riff/wav/infotag.cpp \
  src/taglib/riff/wav/wavfile.cpp \
  src/taglib/riff/wav/wavproperties.cpp \
  src/taglib/s3m/s3mfile.cpp \
  src/taglib/s3m/s3mproperties.cpp \
  src/taglib/tag.cpp \
  src/taglib/tagunion.cpp \
  src/taglib/tagutils.cpp \
  src/taglib/toolkit/tbytevector.cpp \
  src/taglib/toolkit/tbytevectorlist.cpp \
  src/taglib/toolkit/tbytevectorstream.cpp \
  src/taglib/toolkit/tdebug.cpp \
  src/taglib/toolkit/tdebuglistener.cpp \
  src/taglib/toolkit/tfile.cpp \
  src/taglib/toolkit/tfilestream.cpp \
  src/taglib/toolkit/tiostream.cpp \
  src/taglib/toolkit/tpropertymap.cpp \
  src/taglib/toolkit/trefcounter.cpp \
  src/taglib/toolkit/tstring.cpp \
  src/taglib/toolkit/tstringlist.cpp \
  src/taglib/toolkit/tzlib.cpp \
  src/taglib/trueaudio/trueaudiofile.cpp \
  src/taglib/trueaudio/trueaudioproperties.cpp \
  src/taglib/wavpack/wavpackfile.cpp \
  src/taglib/wavpack/wavpackproperties.cpp \
  src/taglib/xm/xmfile.cpp \
  src/taglib/xm/xmproperties.cpp \
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

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

