import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.0
import QSettings 1.0
import Library 1.0
import 'Style'

Page {
    id: root_settings
    title: qsTr("Settings")

    header: Rectangle {
        id: tool_bar
        Layout.fillWidth: true
        height: back_button.height
        color: Style.app.color

        RowLayout {
            id: tool_row
            anchors.fill: parent

            Button {
                id: back_button
                text: "Back"
                onClicked: {
                    stack_view.pop()
                }
            }
            Label {
                text: root_settings.title
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Rectangle {
        id: content
        color: Style.app.color
        anchors.fill: parent


        FileDialog {
            id: file_dialog
            title: "Library"
            folder: shortcuts.home
            selectFolder: true
            onAccepted: {
                Library.path = folder;
            }
            onRejected: {
            }
            //Component.onCompleted: visible = true
        }

        ColumnLayout {
            id: column_layout
            width: parent.width


            Rectangle {
                id: library_path
                color: Style.search.color_background
                implicitHeight: font_scale_spin.height
                implicitWidth: content.width

                Label {
                    text: 'Library Path'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    anchors.margins: Style.settings.margin
                }

                Button {
                    id: library_path_picker
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    onClicked: {
                        file_dialog.visible = true;
                    }
                }
            }


            Rectangle {
                id: radar_enabled
                color: Style.search.color_background
                implicitHeight: radar_check.height
                implicitWidth: content.width

                Label {
                    text: 'Radar Enabled'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    anchors.margins: Style.settings.margin
                }

                CheckBox {
                    id: radar_check
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    checked: root.radar_enabled
                    onCheckedChanged: {
                        root.radar_enabled = checked;
                        QSettings.setValue('radar_enabled', checked)
                    }
                }
            }


        }
    }

}

