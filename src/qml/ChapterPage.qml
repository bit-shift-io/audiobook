import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Player 1.0
import ChapterModel 1.0
import "Style"

Page {
    id: root_chapter_page
    anchors.fill: parent

    background: Rectangle {
        color: Style.app.color
    }

    header: Item {
        id: player_header
        height: title_label.height
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        Label {
            id: title_label
            font.pixelSize: Style.control.font_size_title
            text: Player.titleText
        }

        ImageButton {
            id: menu_button
            imageSource: 'qrc:/ellipsis-v-solid.svg'
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked: {
                drawer.open();
            }
        }
    }



    ListView {
        id: chapter_list
        anchors.fill: parent

        boundsBehavior: Flickable.DragOverBounds
        //snapMode: ListView.SnapToItem
        Layout.fillHeight: true
        Layout.fillWidth: true
        clip: true
        spacing: Style.library.list_spacing
        currentIndex: -1 // no selected default
        ScrollBar.vertical: ScrollBar {}

        model: ChapterModel {

        }

        delegate: Component {
            id: chapter_delegate

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
                            text:  model.duration
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        chapter_list.currentIndex = index;
                        console.log(model.title)
                        // TODO: player.chapter
                    }
                }
            }
        }
    }


}

