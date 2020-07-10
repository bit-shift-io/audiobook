import QtQuick 2.12
import QtQuick.Controls 2.3

AbstractButton {
    id: button

    width: 40
    height: 40

    property int edge: Qt.TopEdge
    property alias imageSource: image.source

    contentItem: Image {
        id: image
        fillMode: Image.Pad
        sourceSize {
            width: button.width
            height: button.height
        }
    }

    background: Rectangle {
        color: Style.button.color_background
    }
}
