import QtQuick 2.12
import QtQuick.Templates 2.2 as T

T.Slider {
    id: control

    implicitWidth: 200
    implicitHeight: 30
    live: true

    handle: Rectangle {
        x: control.visualPosition * (control.width - width)
        y: (control.height - height) / 2
        width: 10
        height: 10
        color: control.pressed ? Style.slider.color_handle_pressed : Style.slider.color_handle
    }

    background: Rectangle {
        y: (control.height - height) / 2
        height: 10
        color: Style.slider.color_background

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: Style.slider.color_progress
        }
    }
}
