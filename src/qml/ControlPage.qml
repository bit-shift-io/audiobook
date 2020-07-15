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

    Item {
        id: timeline
        height: progress.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Label {
            id: track_position
            text: "00:00:00"
        }

        Slider {
            id: progress
            width: parent.width
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            value: Player.progress
            from: 0
            to: 10000
        }

        Label {
            id: track_time
            text: "00:00:00"
            anchors.right: parent.right
        }
    }



    Grid {
        x: 0
        anchors.top: timeline.bottom
        anchors.topMargin: 6
        columns: 3
        spacing: Style.control.spacing

        ImageButton {
            id: step_backward
            imageSource: 'qrc:/step-backward-solid.svg'
            onClicked: {
                Player.skipBackward()
            }
        }

        ImageButton {
            id: play
            imageSource: 'qrc:/play-solid.svg'
            onClicked: {
                state = 'pause'

                if (Player.audioAvailable)
                    Player.togglePlayPause()

                if (Player.state === Player.PlayingState)
                    state = 'play'
            }
            states: [
                State {
                    name: 'play'
                    when: play.checked
                    PropertyChanges {
                        target: play
                        imageSource: 'qrc:/pause-solid.svg'
                    }
                },
                State {
                    name: 'pause'
                    when: !play.checked
                    PropertyChanges {
                        target: play
                        imageSource: 'qrc:/play-solid.svg'
                    }
                }
            ]
        }

        ImageButton {
            id: step_forward
            imageSource: 'qrc:/step-forward-solid.svg'
            onClicked: {
                Player.skipForward()
            }
        }

        ImageButton {
            id: bookmark
            imageSource: 'qrc:/bookmark-solid.svg'
        }

        ImageButton {
            id: mode
            imageSource: 'qrc:/long-arrow-alt-right-solid.svg'
            onClicked: {
                //Player.setPlaybackMode();
            }
        }

        ImageButton {
            id: menu
            imageSource: 'qrc:/bars-solid.svg'
            onClicked: {
                drawer.open();
            }
        }

        ImageButton {
            id: volume_down
            imageSource: 'qrc:/volume-down-solid.svg'
            onClicked: {
                Player.volumeUp();
            }
        }

        ImageButton {
            id: volume_up
            imageSource: 'qrc:/volume-up-solid.svg'
            onClicked: {
                Player.volumeDown();
            }
        }
    }

}

