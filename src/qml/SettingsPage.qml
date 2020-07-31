import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.0
import QSettings 1.0
import QtQml.Models 2.2
import Database 1.0
import Player 1.0
import 'Style'

Page {
    id: root_settings
    padding: Style.app.margin
    title: qsTr("Settings")

    background: Rectangle {
        color: Style.app.color
    }

    header: Item {
        id: tool_bar
        Layout.fillWidth: true
        height: back_button.height

        Button {
            id: back_button
            text: "<"
            onClicked: {
                stack_view.pop()
            }
        }

        Label {
            text: root_settings.title
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
        }

    }

    Item {
        id: content
        anchors.fill: parent

        ColumnLayout {
            id: column_layout
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            Item {
                id: library_path_row
                implicitHeight: library_path_label.height + library_path.height + Style.settings.margin * 2
                implicitWidth: content.width
                anchors.margins: Style.settings.margin

                Label {
                    id: library_path_label
                    text: 'Library Path'
                    font.pixelSize: Style.settings.size_heading
                    font.weight: Style.settings.weight_heading
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: library_path
                    anchors.top: library_path_label.bottom
                    text: Database.libraryPath
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stack_view.push("FilePicker.qml");
                    }
                }
            }

            Separator {}

            Item {
                id: font_scale_row
                implicitHeight: font_scale_label.height + font_scale_desc.height + Style.settings.margin * 2
                implicitWidth: content.width

                Label {
                    id: font_scale_label
                    text: 'Font Scale'
                    font.pixelSize: Style.settings.size_heading
                    font.weight: Style.settings.weight_heading
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: font_scale_desc
                    anchors.top: font_scale_label.bottom
                    text: 'Scale of application fonts'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                SpinBox {
                    id: font_scale_spin
                    value: QSettings.value('font_scale', 100)
                    from: 50
                    to: 200
                    stepSize: 10
                    editable: true
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    anchors.verticalCenter: parent.verticalCenter
                    onValueChanged: {
                        Style.font_scale = value / 100;
                        QSettings.setValue('font_scale', value);
                    }
                }
            }

            Separator {}

            Item {
                id: sleep_time_row
                implicitHeight: sleep_time_label.height + sleep_time_desc.height + Style.settings.margin * 2
                implicitWidth: content.width
                anchors.margins: Style.settings.margin

                Label {
                    id: sleep_time_label
                    text: 'Sleep Duration'
                    font.pixelSize: Style.settings.size_heading
                    font.weight: Style.settings.weight_heading
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: sleep_time_desc
                    anchors.top: parent.children[0].bottom
                    text: 'Sleep timmer duration'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: sleep_time_value
                    text: Player.sleepTimeText
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stack_view.push("DurationPicker.qml");
                    }
                }
            }

            Separator {}

            Item {
                id: repeat_library_row
                implicitHeight: repeat_library_label.height + repeat_library_desc.height + Style.settings.margin * 2
                implicitWidth: content.width


                Label {
                    id: repeat_library_label
                    text: 'Repeat Mode'
                    font.pixelSize: Style.settings.size_heading
                    font.weight: Style.settings.weight_heading
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: repeat_library_desc
                    anchors.top: repeat_library_label.bottom
                    text: 'Repeat item when playing'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.margins: Style.settings.margin
                }

                Label {
                    id: repeat_mode_value
                    text: Player.repeatModeText
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        contextMenu.popup()
                    }

                    Menu {
                        id: contextMenu
                        MenuItem { text: "Library"; onClicked: Player.repeatMode = Player.LIBRARY }
                        MenuItem { text: "Book"; onClicked: Player.repeatMode = Player.BOOK}
                        MenuItem { text: "Chapter"; onClicked: Player.repeatMode = Player.CHAPTER }
                        MenuItem { text: "None"; onClicked: Player.repeatMode = Player.NONE }
                    }
                }
            }

            Separator {}


        }
    }

}

