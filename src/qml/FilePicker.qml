import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.0
import QSettings 1.0
import QtQml.Models 2.2

import Library 1.0
import 'Style'

Page {
    property string current_path: Library.path

    id: root_file_picker
    title: qsTr("File Picker")

    header: Rectangle {
        id: tool_bar
        Layout.fillWidth: true
        height: cancel_button.height
        color: Style.app.color

        RowLayout {
            id: tool_row
            anchors.fill: parent

            Button {
                id: cancel_button
                text: "Cancel"
                Layout.fillWidth: true
                onClicked: {
                    current_path = Library.path;
                    file_list_view.model.folder = Library.path;
                    stack_view.pop()
                }
            }
            Button {
                id: okay_button
                text: "Okay"
                Layout.fillWidth: true
                onClicked: {
                    Library.path = current_path
                    stack_view.pop()
                }
            }
        }
    }

    Rectangle {
        color: Style.app.color
        anchors.fill: parent

        ListView {
            id: file_list_view
            anchors.fill: parent
            model: FileProxyModel
            delegate: Component {
                id: file_delegate

                Item {
                    id: background

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
                                text: model.fileName
                            }
                        }

                        ColumnLayout {
                            id: test2
                            implicitWidth: parent.width
                            Layout.margins: Style.app.margin
                            spacing: 10
                            Layout.alignment: Qt.AlignRight

                            Label {
                                text:  model.filePath
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            file_list_view.model.folder = filePath
                            root_file_picker.current_path = filePath
                        }

                    }
                }
            }
        }
    }
}


