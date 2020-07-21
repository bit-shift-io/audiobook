import QtQuick.Layouts 1.2
import QtQuick 2.12
import QtQuick.Controls 2.12
import "Style"
import Player 1.0

Page {
    id: drawer_page_root
    anchors.fill: parent
    anchors.margins: -1 // some bug with the drawer
    padding: Style.app.margin

    background: Rectangle {
        color: Style.app.color
    }

    ColumnLayout {
        id: column_layout
        width: parent.width


        Button {
            text: "Settings"
            implicitWidth: parent.width
            onClicked: {
                stack_view.push("SettingsPage.qml");
                drawer.close();
            }
        }

        Button {
            text: "Library"
            implicitWidth: parent.width
            onClicked: {
                root.active_swipe_view = 1;
                drawer.close();
            }
        }

        Item {
            id: volume_item
            implicitWidth: parent.width
            implicitHeight: volume_label.height + volume_slider.height

            Label {
                id: volume_label
                text: 'Volume'
            }

            Slider {
                id: volume_slider
                anchors.top: volume_label.bottom
                width: parent.width
                from: 0
                to: 100
                value: Player.volume
                snapMode: Slider.SnapAlways
                stepSize: 25

                onPressedChanged: {
                    Player.volume = value;
                }
            }
        }

        Item {
            id: speed_item
            implicitWidth: parent.width
            implicitHeight: speed_label.height + speed_slider.height

            Label {
                id: speed_label
                text: 'Playback Speed'
            }

            Slider {
                id: speed_slider
                anchors.top: speed_label.bottom
                width: parent.width
                from: 0.5
                to: 1.5
                value: Player.speed
                snapMode: Slider.SnapAlways
                stepSize: 0.1

                onPressedChanged: {
                    Player.speed = value;
                }
            }
        }

        Button {
            text: "Exit"
            implicitWidth: parent.width
            onClicked: {
                stack_view.pop();
                drawer.close();
                Qt.quit();
            }
        }
    }
}
