import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import Database 1.0
import Player 1.0
import "Style"

Page {
    id: root_library_page
    anchors.fill: parent

    background: Rectangle {
        color: Style.app.color_2
    }

    header:
        Rectangle {
            id: library_header
            height: library_filter.height + Style.app.margin * 2
            color: Style.app.color
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            TextField {
                id: library_filter
                placeholderText: qsTr("Search")
                cursorVisible: true
                focus: true
                anchors.margins: Style.app.margin
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top

                onTextChanged: {
                    //library_list.currentIndex = -1;
                    LibraryFilterProxy.setFilterRegExp(text);
                }
            }
        }



    ListView {
        id: library_list
        anchors.fill: parent

        boundsBehavior: Flickable.DragOverBounds
        //snapMode: ListView.SnapToItem
        Layout.fillHeight: true
        Layout.fillWidth: true
        clip: true
        spacing: Style.library.list_spacing
        currentIndex: -1 // no selected default
        ScrollBar.vertical: ScrollBar {}

        model: LibraryFilterProxy

        delegate: Component {
            id: search_delegate

            Rectangle {
                id: background
                color: model.isCurrentItem? Style.library.color_highlight : Style.library.color_background
                radius: Style.library.radius_background
                implicitHeight: library_title.height + library_artist.height + Style.library.margin * 3
                implicitWidth: library_list.width

                ListSeparator {
                    listView: library_list
                }

                Label {
                    id: library_title
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: Style.library.margin
                    text: model.title
                    font.pixelSize: Style.library.size_heading
                    elide: Text.ElideRight
                }

                Label {
                    id: library_artist
                    anchors.top: library_title.bottom
                    anchors.left: parent.left
                    anchors.margins: Style.library.margin
                    text: model.artist
                }

                Label {
                    id: library_duration
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: Style.library.margin
                    text:  model.chapters + ' | ' + model.duration
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        library_list.currentIndex = index;
                        Player.currentItem = model.path;
                    }
                    onDoubleClicked: {
                        //library_list.currentIndex = index;
                        //Player.currentItem = model.path;
                        Player.play();
                    }
                }
            }
        }
    }

}
