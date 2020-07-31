import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.2
import 'Style'

Dialog {
    property alias currentIndex: popup_list_view.currentIndex
    property var model: []

    Component.onCompleted: {
        for (var i=0; i<model.length; i++) {
            popup_list_model.append(model[i]);
        }
    }

    id: control
    padding: Style.app.margin
    implicitWidth: 200
    implicitHeight: 200
    anchors.centerIn: parent

    background: Rectangle {
        color: Style.app.color
    }

    footer:
        Item {
            id: tool_bar
            Layout.fillWidth: true
            height: cancel_button.height

            RowLayout {
                id: tool_row
                anchors.fill: parent

                Button {
                    id: cancel_button
                    text: 'Cancel'
                    Layout.fillWidth: true
                    onClicked: {
                        reject();
                    }
                }

                Button {
                    id: okay_button
                    text: 'Okay'
                    Layout.fillWidth: true
                    onClicked: {
                        accept();
                    }
                }
            }
        }


    ListModel {
        id: popup_list_model
    }

    Component {
        id: popup_list_delegate

        Rectangle {
            id: background
            color: ListView.isCurrentItem? Style.library.color_highlight : Style.library.color_background
            radius: Style.library.radius_background
            implicitHeight: title.height + Style.library.margin * 2
            implicitWidth: popup_list_view.width


            Label {
                id: title
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.margins: Style.library.margin
                text: model.label
                font.pixelSize: Style.control.font_size_chapter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    popup_list_view.currentIndex = index;
                }
            }
        }
    }

    Item {
        anchors.fill: parent

        ListView {
            id: popup_list_view
            anchors.fill: parent
            clip: true
            currentIndex: -1
            model: popup_list_model
            delegate: popup_list_delegate
        }
    }

}


