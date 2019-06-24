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


# qt resources
set(CMAKE_AUTORCC ON)
qt5_add_resources (RCC_SOURCES res/resources.qrc)

# app config
add_executable(audiobook ${SOURCES} ${HEADERS} ${UI} ${RCC_SOURCES})

# taglib configuration
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
find_package( TAGLIB REQUIRED )
if ( TAGLIB_FOUND )
    include_directories( ${TAGLIB_INCLUDE_DIRS} )
    target_link_libraries( audiobook ${TAGLIB_LIBRARIES} )
endif( TAGLIB_FOUND )

# app config
target_link_libraries(audiobook Qt5::Widgets)
QT5_USE_MODULES(audiobook Multimedia MultimediaWidgets)
install(TARGETS audiobook DESTINATION bin)

# Do platform specific post target stuff
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(FILES res/io.bit-shift.audiobook.desktop DESTINATION /usr/share/applications ) # /usr/share?
    install(FILES res/io.bit-shift.audiobook.svg DESTINATION /usr/share/pixmaps ) # /usr/share?
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
