cmake_minimum_required(VERSION 3.14)
project(AudioBook)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

set(QT_USE_QTMULTIMEDIA TRUE)
set(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

set(SOURCES 
    src/book.cpp
    src/library.cpp
    src/librarymodel.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/player.cpp
    src/audioutil.cpp
    src/stretchingheader.cpp
)

set(HEADERS
    src/book.h
    src/library.h
    src/librarymodel.h
    src/mainwindow.h
    src/player.h
    src/audioutil.h
    src/stretchingheader.h
)

set(UI
    src/mainwindow.ui
)

# taglib configuration
set(TAGLIB_VERSION 1.11.1)
set(TAGLIB_CHECKSUM "cee7be0ccfc892fa433d6c837df9522a")
include(ExternalProject)

# TagLib
ExternalProject_Add(
    taglib
    URL https://taglib.org/releases/taglib-${TAGLIB_VERSION}.tar.gz
    URL_MD5 ${TAGLIB_CHECKSUM}
    CONFIGURE_COMMAND ${CMAKE_COMMAND}
                      ${CMAKE_CURRENT_BINARY_DIR}/taglib/src/taglib
                      -DCMAKE_MAKE_PROGRAM=${UNIX_MAKE_PROGRAM}
                      -DBUILD_SHARED_LIBS=ON
                      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/build/taglib/

    PREFIX taglib
    INSTALL_COMMAND ${UNIX_MAKE_PROGRAM} install
)
add_library(tag SHARED IMPORTED)
set_target_properties(tag PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/build/taglib/lib/libtag.so)


add_executable(audiobook ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(audiobook Qt5::Widgets)
QT5_USE_MODULES(audiobook Multimedia MultimediaWidgets)
install(TARGETS audiobook DESTINATION bin)

# Do platform specific post target stuff
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(FILES resources/io.bit-shift.audiobook.desktop DESTINATION /usr/share/applications ) # /usr/share?
    install(FILES resources/io.bit-shift.audiobook.svg DESTINATION /usr/share/pixmaps ) # /usr/share?
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
