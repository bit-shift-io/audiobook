import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.0
import QSettings 1.0
import QtQml.Models 2.2

import Library 1.0
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

    Item {
        id: content
        anchors.fill: parent

        ColumnLayout {
            id: column_layout
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            Rectangle {
                id: library_path_row
                color: Style.settings.color_background
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
                    text: Library.path
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

            Spacer {}

            Rectangle {
                id: font_scale
                color: Style.settings.color_background
                implicitHeight: font_scale_spin.height
                implicitWidth: content.width

                Label {
                    text: 'Font Scale'
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    anchors.margins: Style.settings.margin
                }

                SpinBox {
                    id: font_scale_spin
                    value: QSettings.value('font_scale', 100)
                    from: 50
                    to: 200
                    Layout.alignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.margins: Style.settings.margin
                    onValueChanged: {
                        Style.font_scale = value / 100;
                        QSettings.setValue('font_scale', value);
                    }
                }
            }

            Spacer {}

            Rectangle {
                id: radar_enabled
                color: Style.settings.color_background
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
                    checked: false
                    onCheckedChanged: {
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(parent.id);
                    }
                }
            }

            Spacer {}


        }
    }

}

