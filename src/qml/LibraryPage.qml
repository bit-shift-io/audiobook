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

    Component.onCompleted: {
        console.log(Library.path);
        console.log(Library.size);
    }

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
                implicitHeight: row_layout.height
                implicitWidth: parent.width

                RowLayout {
                    id: row_layout
                    Layout.fillWidth: true
                    width: parent.width

                    ColumnLayout {
                        id: test
                        implicitWidth: parent.width
                        Layout.margins: Style.library.margin
                        spacing: 10
                        Layout.alignment: Qt.AlignLeft

                        Label {
                            text: model.title
                        }
                    }

                    ColumnLayout {
                        id: test2
                        implicitWidth: parent.width
                        Layout.margins: Style.app.margin
                        spacing: 10
                        Layout.alignment: Qt.AlignRight

                        Label {
                            text:  model.chapters + ' | ' + model.duration
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        library_list.currentIndex = index;
                        console.log(model.title)
                        Library.activeItem = model.libraryIndex;
                    }
                }
            }
        }
    }

}
