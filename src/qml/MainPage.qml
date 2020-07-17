import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0
import 'Style'

Page {
    id: root_main_page

    background: Rectangle {
        color: Style.app.color
    }

    header: TabBar {
            id: bar


            TabButton {
                text: qsTr("Playback")
                onClicked: {
                    swipe_view.currentIndex = 0
                }

                Image {
                    source: 'qrc:/play-circle-solid.svg'
                    sourceSize.width: parent.height
                    sourceSize.height: parent.height
                }
            }

            TabButton {
                text: qsTr("Library")
                onClicked: {
                    swipe_view.currentIndex = 1
                }

                Image {
                    source: 'qrc:/photo-video-solid.svg'
                    sourceSize.width: parent.height
                    sourceSize.height: parent.height
                }
            }


            TabButton {
                id: menu_button
                width: height
                Image {
                    id: menu_icon
                    source: 'qrc:/ellipsis-v-solid.svg'
                    sourceSize.width: parent.height
                    sourceSize.height: parent.height
                }
                onClicked: {
                    drawer.open();
                }
            }
        }


    SwipeView {
        id: swipe_view
        anchors.fill: parent
        currentIndex: 0

        Item {
            id: firstPage
            ControlPage {

            }
        }

        Item {
            id: secondPage
            LibraryPage {

            }
        }
    }

    // https://appbus.wordpress.com/2016/06/07/tab-pages-app-tabbar/
    // https://github.com/ekke/tab_pages_x


}
