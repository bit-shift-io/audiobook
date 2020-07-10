import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Player 1.0
import "Style"

Page {
    id: root_control_page
    anchors.fill: parent

    background: Rectangle {
        color: Style.app.color
    }

    Grid {
        columns: 3
        spacing: 2

        ImageButton {
            id: step_backward
            imageSource: 'qrc:/step-backward-solid.svg'
        }

        ImageButton {
            id: play
            imageSource: 'qrc:/play-solid.svg'
            onClicked: {
                Player.playUrl();
            }
        }

        ImageButton {
            id: step_forward
            imageSource: 'qrc:/step-forward-solid.svg'
        }

        ImageButton {
            id: bookmark
            imageSource: 'qrc:/bookmark-solid.svg'
        }

        ImageButton {
            id: mode
            imageSource: 'qrc:/long-arrow-alt-right-solid.svg'
        }

        ImageButton {
            id: menu
            imageSource: 'qrc:/bars-solid.svg'
        }


        ImageButton {
            id: volume_mute
            imageSource: 'qrc:/volume-mute-solid.svg'
        }

        ImageButton {
            id: volume_down
            imageSource: 'qrc:/volume-down-solid.svg'
        }

        ImageButton {
            id: volume_up
            imageSource: 'qrc:/volume-up-solid.svg'
        }
    }

}

