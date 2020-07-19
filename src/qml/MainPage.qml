import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

import Player 1.0
import 'Style'

Page {
    id: root_main_page
    padding: Style.app.margin

    background: Rectangle {
        color: Style.app.color
    }


    SwipeView {
        id: swipe_view
        clip: true
        anchors.top: parent.top
        anchors.bottom: player_timeline.top
        anchors.right: parent.right
        anchors.left: parent.left


        Item {
            id: firstPage
            ChapterPage {

            }
        }

        Item {
            id: secondPage
            LibraryPage {

            }
        }
    }


    Item {
        id: player_timeline
        height: progress.height + time_row.height
        anchors.bottom: playback_control.top
        anchors.right: parent.right
        anchors.left: parent.left

        Slider {
            id: progress
            width: parent.width
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            live: false

            handle: Item { // hide handle
                id: pill
                width: 0
                height: 0
            }
            value: Player.progress;
            from: 0
            to: 10000
            onPressedChanged: {
                if(!pressed)
                    Player.setProgress(value);
            }
        }

        Row {
            id: time_row
            height: track_time.height
            anchors.top: progress.bottom
            anchors.right: parent.right
            anchors.left: parent.left

            Label {
                id: track_position
                text: Player.positionText
            }

            Label {
                id: chapter_progress
                text: Player.chapterProgressText
                anchors.centerIn: parent
            }

            Label {
                id: track_time
                text: Player.timeText
                anchors.right: parent.right
            }
        }


    }

    Row {
        id: playback_control
        width: parent.width
        height: play_button.height
        anchors.bottom: parent.bottom

        ImageButton {
            id: timmer_button
            anchors.left: parent.left
            imageSource: 'qrc:/stopwatch-solid.svg'
            onClicked: {
                Player.skipBackward()
            }
        }

        ImageButton {
            id: step_backward_button
            anchors.right: play_button.left
            imageSource: 'qrc:/step-backward-solid.svg'
            onClicked: {
                Player.skipBackward()
            }
        }

        ImageButton {
            id: play_button
            anchors.centerIn: playback_control
            imageSource: 'qrc:/play-circle-solid.svg'

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
                    when: play_button.checked
                    PropertyChanges {
                        target: play_button
                        imageSource: 'qrc:/pause-solid.svg'
                    }
                },
                State {
                    name: 'pause'
                    when: !play_button.checked
                    PropertyChanges {
                        target: play_button
                        imageSource: 'qrc:/play-circle-solid.svg'
                    }
                }
            ]
        }

        ImageButton {
            id: step_forward_button
            anchors.left: play_button.right
            imageSource: 'qrc:/step-forward-solid.svg'
            onClicked: {
                Player.skipForward()
            }
        }

        ImageButton {
            id: speed_button
            anchors.right: parent.right
            imageSource: 'qrc:/step-forward-solid.svg'
            onClicked: {
                Player.skipForward()
            }
        }
    }

}
