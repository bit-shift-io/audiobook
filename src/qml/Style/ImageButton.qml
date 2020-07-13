import QtQuick 2.12
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

AbstractButton {
    id: button

    width: 40
    height: 40

    property alias imageSource: image.source

    contentItem: Image {
        id: image
        fillMode: Image.Pad
        visible: true
        smooth: true
        sourceSize {
            width: button.width
            height: button.height
        }

        ColorOverlay {
            anchors.fill: parent
            source: parent
            color: Style.image_button.color_foreground
        }
    }

    background: Rectangle {
        color: Style.image_button.color_background
    }
}
