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
        id: player_navigation
        height: bookmark_button.height
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        ComboBox {
            id: bookmark_button
            anchors.left: parent.left
            currentIndex: 0
            model: 30
            onActivated: {
            }
        }

        /*
        ImageButton {
            id: bookmark_button
            anchors.left: parent.left
            imageSource: 'qrc:/bookmark-solid.svg'
            onClicked: {
                chapter_dialog.open();
            }

            Dialog {
                id: chapter_dialog
                modal: true
                standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                contentItem:
                    ListView {
                        id: hour_tumbler
                        model: 12
                        onCurrentIndexChanged:{}
                    }

            }
        }*/

        ComboBox {
            id: mode_button
            anchors.left: bookmark_button.right
            currentIndex: 0
            model: ListModel {
                id: mode_items
                ListElement { text: 'Sequential'; image: 'qrc:/bookmark-solid.svg' }
                ListElement { text: 'CurrentItemInLoop'; image: 'qrc:/bookmark-solid.svg' }
                ListElement { text: 'Loop'; image: 'qrc:/bookmark-solid.svg' }
            }
            onActivated: {
                Player.setPlaybackMode(model[index].text);
            }
        }

        Label {
            id: title
            font.pixelSize: Style.control.font_size_title
            anchors.left: mode_button.right
            text: Player.titleText
        }

        Label {
            id: chapter
            font.pixelSize: Style.control.font_size_chapter
            anchors.left: menu_button.right
            text: Player.chapterText
        }
    }

    Item {
        id: player_timeline
        height: progress.height
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: player_navigation.bottom

        Label {
            id: track_position
            text: Player.positionText
        }

        Slider {
            id: progress
            width: parent.width
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            value: {
                if (!pressed)
                    Player.progress;
            }
            from: 0
            to: 10000
            onPressedChanged: {
                if(!pressed)
                    Player.setProgress(value);
            }
        }

        Label {
            id: track_time
            text: Player.timeText
            anchors.right: parent.right
        }
    }

    Grid {
        id: playback_control
        anchors.top: player_timeline.bottom
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
    }

    Item {
        id: volume_control
        anchors.top: playback_control.bottom
        Slider {
            id: volume_slider
            value: Player.volume
            from: 0
            to: 100
        }

        /*
        ImageButton {
            id: volume_down
            imageSource: 'qrc:/volume-down-solid.svg'
            onClicked: {
                Player.volumeDown();
            }
        }

        ImageButton {
            id: volume_up
            imageSource: 'qrc:/volume-up-solid.svg'
            onClicked: {
                Player.volumeUp();
            }
        }
        */
    }

}

