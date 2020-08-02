import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import Qt.labs.folderlistmodel 2.1
import QtGraphicalEffects 1.0
import Database 1.0
import Util 1.0
import 'Style'

Page {
    id: root_file_picker
    title: qsTr("File Picker")
    padding: Style.app.margin

    background: Rectangle {
        color: Style.app.color
    }

    header: Item {
        id: tool_bar
        Layout.fillWidth: true
        height: cancel_button.height

        RowLayout {
            id: tool_row
            anchors.fill: parent

            Button {
                id: cancel_button
                text: "Cancel"
                Layout.fillWidth: true
                onClicked: {
                    file_list_view.model.folder = "file://" + Database.libraryPath
                    stack_view.pop()
                }
            }

            Button {
                id: okay_button
                text: "Okay"
                Layout.fillWidth: true
                onClicked: {
                    Database.libraryPath = folder_list_model.folder
                    stack_view.pop()
                }
            }
        }
    }

    ComboBox {
        id: extra_paths
        anchors.top: parent.top
        implicitWidth: parent.width
        visible: Util.getAndroidStorageLocations().length > 0
        model: Util.getAndroidStorageLocations()
        onCurrentIndexChanged: {
            folder_list_model.folder = 'file://' + Util.getAndroidStorageLocations()[currentIndex] + '/'
            console.log('file://' + Util.getAndroidStorageLocations()[currentIndex] + '/')
            console.log('file://' + Database.libraryPath)
        }
    }

    ListView {
        id: file_list_view
        anchors.top: Util.getAndroidStorageLocations().length > 0 ? extra_paths.bottom : parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        clip: true
        ScrollBar.vertical: ScrollBar {}

        model: FolderListModel {
            id:  folder_list_model
            showDotAndDotDot: true
            showHidden: false
            showDirsFirst: true
            showFiles: true
            folder: "file://" + Database.libraryPath
            nameFilters: "*.*"
        }

        delegate: Component {
            id: file_delegate

            Item {
                id: file_row
                implicitHeight: file_name_label.height + Style.app.margin * 2
                implicitWidth: file_list_view.width
                anchors.margins: Style.app.margin

                Image {
                    id: icon_type
                    anchors.margins: Style.app.margin
                    source: folder_list_model.isFolder(model.index) ? "qrc:/folder-solid.svg" : "qrc:/file-alt-solid.svg"
                    fillMode: Image.PreserveAspectFit
                    visible: true
                    smooth: true

                    sourceSize {
                        width: file_name_label.height
                        height: file_name_label.height
                    }

                    ColorOverlay {
                        anchors.fill: parent
                        source: parent
                        color: Style.image_button.color_foreground
                    }
                }

                Label {
                    id: file_name_label
                    text: model.fileName
                    anchors.left: icon_type.right
                    anchors.leftMargin: Style.app.margin
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(model.fileName === ".." && model.folder !== "file:///") {
                            folder_list_model.folder = folder_list_model.parentFolder
                        } else if (fileName !== ".") {
                            if(folder_list_model.folder === "file:///") {
                                folder_list_model.folder += fileName
                            } else {
                                folder_list_model.folder += "/" + fileName
                            }
                        }
                    }
                }
            }

        }

    }
}


