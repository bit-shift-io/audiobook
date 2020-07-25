import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

import Player 1.0
import 'Style'

Page {
    id: root_main_page
    //padding: Style.app.margin

    background: Rectangle {
        color: Style.app.color
    }

    Connections {
        target: Player
        function onStateChanged(xState) {
            console.log(xState)
            if (Player.state === Player.PlayingState) {
                root.active_swipe_view = 0;
                console.log("change swipe view");
            }
        }
    }

    SwipeView {
        id: swipe_view
        clip: true
        anchors.top: parent.top
        anchors.bottom: item_control.top
        anchors.right: parent.right
        anchors.left: parent.left
        currentIndex: root.active_swipe_view


        Item {
            ChapterPage {}
        }

        Item {
            LibraryPage {}
        }
    }


    Item {
        id: item_control
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: Style.app.margin
        height: player_timeline.height + playback_control.height


        Item {
            id: player_timeline
            height: progress.height + time_row.height + Style.app.margin * 2
            anchors.bottom: playback_control.top
            anchors.right: parent.right
            anchors.left: parent.left

            Slider {
                id: progress
                width: parent.width
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.topMargin: Style.app.margin
                live: false
                value: Player.sliderValue;
                from: 0
                to: 10000
                onPressedChanged: {
                    if(!pressed)
                        Player.setSliderValue(value);
                }
            }

            Item {
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

        Item {
            id: playback_control
            width: parent.width
            height: play_button.height
            anchors.bottom: parent.bottom

            ImageButton {
                id: timmer_button
                anchors.left: parent.left
                imageSource: 'qrc:/stopwatch-solid.svg'
                imagePadding: Style.image_button.padding_small
                onClicked: {
                    Player.skipBackward()
                }
            }

            ImageButton {
                id: step_backward_button
                anchors.right: play_button.left
                anchors.rightMargin: play_button.width * 0.2
                imageSource: 'qrc:/step-backward-solid.svg'
                imagePadding: Style.image_button.padding_small
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
                anchors.leftMargin: play_button.width * 0.2
                imageSource: 'qrc:/step-forward-solid.svg'
                imagePadding: Style.image_button.padding_small
                onClicked: {
                    Player.skipForward()
                }
            }

            ImageButton {
                id: menu_button
                imageSource: 'qrc:/bars-solid.svg'
                imagePadding: Style.image_button.padding_small
                anchors.right: parent.right
                onClicked: {
                    drawer.open();
                }
            }
        }

    }


}
