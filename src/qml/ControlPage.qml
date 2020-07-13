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

    Slider {
        id: progress
        from: 0
        value: Player.position
        to: 10000
    }

    Grid {
        columns: 3
        spacing: 2

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
            checkable: true
            onClicked: {
                Player.togglePlayPause()
            }
            states: [
                State {
                    name: "play"
                    when: play.checked
                    PropertyChanges {
                        target: play
                        imageSource: 'qrc:/pause-solid.svg'
                    }
                },
                State {
                    name: "pause"
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

