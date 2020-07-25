import QtQuick 2.12
import QtQuick.Templates 2.12 as T

T.TextField {
    id: control

    font.pixelSize: Style.text_field.font_size
    font.weight: Style.text_field.font_weight
    color: Style.text_field.font_color
    horizontalAlignment: TextInput.AlignHCenter
    verticalAlignment: TextInput.AlignVCenter
    bottomInset: 2

    implicitWidth: background ? background.implicitWidth : 0
    implicitHeight: background ? background.implicitHeight : 0
    leftPadding: 4
    rightPadding: 4

    cursorDelegate:
        Rectangle {
            id: cursor_rectangle
            implicitHeight: Style.text_field.font_size
            implicitWidth: 2
            color: Style.text_field.font_color
        }

    background: Rectangle {
        id: buttonBackground
        implicitWidth: 100
        implicitHeight: Style.text_field.font_size + bottomInset + topInset + Style.app.margin * 2
        opacity: enabled ? 1 : 0.3
        color: Style.text_field.color_background_normal
        //border.color: Style.button.color_background
        //border.width: 1
        radius: 0

        Rectangle {
            id: bottom_inset
            implicitWidth: parent.width
            implicitHeight: bottomInset
            anchors.bottom: parent.bottom
            color: Style.text_field.color_inset_normal
        }



        states: [
            State {
                name: "normal"
                when: !control.down
                PropertyChanges {
                    target: buttonBackground
                }
            },
            State {
                name: "focused"
                when: control.down
                PropertyChanges {
                    target: buttonBackground
                    color: Style.text_field.color_background_focused
                }
                PropertyChanges {
                    target: bottom_inset
                    color: Style.text_field.color_inset_focused
                }
            },
            State {
                name: "disabled"
                when: control.down
                PropertyChanges {
                    target: buttonBackground
                    color: Style.text_field.color_background_disabled
                }
                PropertyChanges {
                    target: bottom_inset
                    color: Style.text_field.color_inset_disabled
                }
            }
        ]
    }

}
