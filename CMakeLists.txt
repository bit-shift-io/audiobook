cmake_minimum_required(VERSION 3.14)
project(AudioBook)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
if(UNIX) # Enable C++11 features for clang and gcc
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
endif()

################# Debug Flags #################

# enable debug via cmd
# cmake -DDEFINE_DEBUG=ON -DCMAKE_INSTALL_PREFIX=/usr ..
option(DEFINE_DEBUG
  "Build using debug"
  OFF)

if(DEFINE_DEBUG)
  message("Adding Debug flag...")
  add_definitions(-DDEBUG)
  set(CMAKE_BUILD_TYPE Debug)
  message("Build type is " ${CMAKE_BUILD_TYPE})
endif()

# debug, enable debugging
# https://doc.qt.io/qt-5/qtquick-debugging.html#qml-debugging-infrastructure

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQT_QML_DEBUG ")
    message(STATUS "debug enabled")
endif()


################# Configure paths #################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>) # /lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>) # /lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>) # /bin

################# QT components #################

# widgets for systray qapplication
# graphical effects for drop shadow
# charts for charts
find_package(Qt5 COMPONENTS REQUIRED Core Quick Svg Sql Multimedia)

#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Core REQUIRED)
#find_package(Qt5Multimedia REQUIRED)
#find_package(Qt5MultimediaWidgets REQUIRED)

#set(QT_USE_QTMULTIMEDIA TRUE)
#set(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

################# Files #################

set(INCLUDES
    src/taglib
    src/taglib/utf8-cpp
    src/taglib/toolkit
    src/taglib/mpeg/id3v1
    src/taglib/mpeg/id3v2
    src/taglib/mpeg/id3v2/frames
    src/taglib/ape
    src/taglib/asf
    src/taglib/flac
    src/taglib/mp4
    src/taglib/mpc
    src/taglib/mpeg
    src/taglib/ogg
    src/taglib/riff
    src/taglib/trueaudio
    src/taglib/wavpack
    src/taglib/ogg/flac
    src/taglib/ogg/speex
    src/taglib/ogg/vorbis
    src/taglib/ogg/opus
    src/taglib/riff/aiff
    src/taglib/riff/wav
    src/taglib/mod
    src/taglib/it
    src/taglib/s3m
    src/taglib/xm
)

set(HEADERS
    src/book.h
    src/chapter.h
    src/chaptermodel.h
    src/database.h
    src/libraryfilterproxy.h
    src/librarymodel.h
    src/player.h
    src/settings.h
    src/shortcuts.h
    src/util.h
)

set(SOURCES 
    src/chaptermodel.cpp
    src/database.cpp
    src/libraryfilterproxy.cpp
    src/librarymodel.cpp
    src/main.cpp
    src/player.cpp
    src/settings.cpp
    src/shortcuts.cpp
    src/util.cpp
)

set(UI
)

set(RESOURCES
    src/qml.qrc
    res/res.qrc
)


################# Target #################

include_directories(${INCLUDES})

# qt resources
set(CMAKE_AUTORCC ON)
qt5_add_resources (RCC_SOURCES res/res.qrc)

# app config
add_executable(audiobook ${SOURCES} ${HEADERS} ${UI} ${RCC_SOURCES})

# app config
target_link_libraries(audiobook Qt5::Core Qt5::Quick Qt5::Sql Qt5::Svg)
QT5_USE_MODULES(audiobook Multimedia)

################# Install #################

install(TARGETS audiobook DESTINATION bin)

# Do platform specific post target stuff
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(FILES res/bitshift.audiobook.desktop DESTINATION share/applications ) # /usr/share?
    install(FILES res/bitshift.audiobook.svg DESTINATION share/pixmaps ) # /usr/share?
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
