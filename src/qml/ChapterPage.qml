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
        color: Style.app.color_2
    }

    header:
        Rectangle {
            id: player_header
            height: title_label.height + Style.app.margin * 2
            color: Style.app.color
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            Label {
                id: title_label
                font.pixelSize: Style.control.font_size_title
                text: Player.titleText
                anchors.margins: Style.app.margin
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                elide: Text.ElideRight
            }
        }



    ListView {
        id: chapter_list
        anchors.fill: parent

        boundsBehavior: Flickable.DragOverBounds
        //snapMode: ListView.SnapToItem
        preferredHighlightBegin: height / 2
        preferredHighlightEnd: height / 2
        highlightRangeMode: ListView.ApplyRange
        Layout.fillHeight: true
        Layout.fillWidth: true
        clip: true
        spacing: Style.library.list_spacing
        currentIndex: Player.chapterIndex
        ScrollBar.vertical: ScrollBar {}

        model: ChapterModel {

        }

        delegate: Component {
            id: chapter_delegate

            Rectangle {
                id: background
                color: ListView.isCurrentItem? Style.library.color_highlight : Style.library.color_background
                radius: Style.library.radius_background
                implicitHeight: row_layout.height
                implicitWidth: chapter_list.width

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
                            font.pixelSize: Style.control.font_size_chapter
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
                        Player.chapterIndex = index;
                    }
                }
            }
        }
    }


}

