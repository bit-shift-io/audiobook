import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import Library 1.0
import Player 1.0
//import LibraryModel 1.0
import "Style"

Page {
    id: root_library_page
    anchors.fill: parent

    background: Rectangle {
        color: Style.app.color
    }

    header: TextField {
        id: library_filter
        placeholderText: qsTr("Search")
        cursorVisible: true
        focus: true

        onTextChanged: {
            //library_list.currentIndex = -1;
            LibraryFilterProxy.setFilterRegExp(text);
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
                color: ListView.isCurrentItem? Style.library.color_highlight : Style.library.color_background // TODO: model.isCurrentItem for active item
                radius: Style.library.radius_background
                implicitHeight: library_title.height + library_artist.height + Style.library.margin * 3
                implicitWidth: parent.width

                Label {
                    id: library_title
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: Style.library.margin
                    text: model.title
                    font.pixelSize: Style.library.size_heading
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
                        Library.currentItem = model.path;
                        console.log(model.path);
                    }
                    onDoubleClicked: {
                        library_list.currentIndex = index;
                        Library.currentItem = model.path;
                        Player.play();
                    }
                }
            }
        }
    }

}
