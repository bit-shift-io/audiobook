import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import Qt.labs.folderlistmodel 2.1
import QtGraphicalEffects 1.0
import Database 1.0
import Player 1.0
import 'Style'

Page {

    property string duration_string: ''
    property int max_duration: -1
    property bool hoursEnabled: true
    property bool minutesEnabled: true
    property bool secondsEnabled: false

    id: control
    title: qsTr('Duration Picker')
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
                text: 'Cancel'
                Layout.fillWidth: true
                onClicked: {
                    stack_view.pop()
                }
            }

            Button {
                id: okay_button
                text: 'Okay'
                Layout.fillWidth: true
                onClicked: {
                    Player.sleepTime = getDurationMSec();
                    stack_view.pop()
                }
            }
        }
    }

    Component.onCompleted: {
        if (hoursEnabled)
            max_duration += 2;
        if (minutesEnabled)
            max_duration += 2;
        if (secondsEnabled)
            max_duration += 2;
    }


    function buttonPressed(xText) {
        if (xText === 'backspace') {
            duration_string = duration_string.substring(0, duration_string.length - 1);
            return;
        }

        if (duration_string.length > max_duration)
            return;

        duration_string += xText;

        if (duration_string === '0')
            duration_string = '';
    }

    function getDuration() {
        var d = duration_string;
        for (var i=duration_string.length; i<=max_duration; i++) {
            d = '0' + d;
        }
        return d;
    }

    function getDurationMSec() {
        var t = 0;
        if (secondsEnabled)
            t += parseInt(getSeconds()) * 1000;
        if (minutesEnabled)
            t += parseInt(getMinutes()) * 60 * 1000;
        if (hoursEnabled)
            t += parseInt(getHours()) * 60 * 60 * 1000;
        console.log(t)
        return t;
    }

    function getHours() {
        if (!hoursEnabled)
            return '';

        var d = getDuration();
        return d.substring(0, 2);
    }

    function getMinutes() {
        if (!minutesEnabled)
            return '';

        var d = getDuration();
        var start = 0;
        if (hoursEnabled)
            start += 2;
        return d.substring(start + 0, start + 2);
    }

    function getSeconds() {
        if (!secondsEnabled)
            return '';

        var d = getDuration();
        var start = 0;
        if (hoursEnabled)
            start += 2;
        if (minutesEnabled)
            start += 2;
        return d.substring(start + 0, start + 2);
    }

    Item {
        id: duration_item
        anchors.fill: parent

        RowLayout {
            id: display
            //implicitWidth: hours.width + minutes.width + seconds.width
            implicitHeight: hours_label.height
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Item {
                id: hours
                visible: hoursEnabled
                implicitHeight: hours_label.height
                implicitWidth: hours_label.width + h_label.width

                Label {
                    id: hours_label
                    text: getHours()
                    font.pixelSize: Style.duration_picker.font_size_digit
                }

                Label {
                    id: h_label
                    text: 'h '
                    font.pixelSize: Style.duration_picker.font_size_text
                    anchors.left: hours_label.right
                    anchors.baseline: hours_label.baseline
                }

            }

            Item {
                id: minutes
                visible: minutesEnabled
                implicitHeight: minutes_label.height
                implicitWidth: minutes_label.width + m_label.width

                Label {
                    id: minutes_label
                    text: getMinutes()
                    font.pixelSize: Style.duration_picker.font_size_digit
                }

                Label {
                    id: m_label
                    text: 'm '
                    font.pixelSize: Style.duration_picker.font_size_text
                    anchors.left: minutes_label.right
                    anchors.baseline: minutes_label.baseline
                }
            }

            Item {
                id: seconds
                visible: secondsEnabled
                implicitHeight: seconds_label.height
                implicitWidth: seconds_label.width + s_label.width

                Label {
                    id: seconds_label
                    text: getSeconds()
                    font.pixelSize: Style.duration_picker.font_size_digit
                }

                Label {
                    id: s_label
                    text: 's'
                    font.pixelSize: Style.duration_picker.font_size_text
                    anchors.left: seconds_label.right
                    anchors.baseline: seconds_label.baseline
                }
            }
        }


        Grid {
            id: number_pad

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            columns: 3
            columnSpacing: 8
            rowSpacing: 8

            signal buttonPressed

            Button { text: '7'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '8'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '9'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '4'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '5'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '6'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '1'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '2'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Button { text: '3'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            Label { text:' ' }
            Button { text: '0'; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed(text) }
            ImageButton { imageSource: 'qrc:/backspace-solid.svg'; imagePadding: 20; font.pixelSize: Style.duration_picker.font_size_button; width: Style.duration_picker.size_button; height: Style.duration_picker.size_button; onClicked: buttonPressed('backspace') }
        }
    }

}


