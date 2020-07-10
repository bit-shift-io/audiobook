import QtQuick 2.12
import QtQuick.Controls 2.3

AbstractButton {
    id: button

    property int edge: Qt.TopEdge
    property alias imageSource: image.source

    contentItem: Image {
        id: image
        fillMode: Image.Pad
        sourceSize { width: 40; height: 40 } // ### TODO: resize the image
    }

    background: Rectangle {
        height: button.height * 4
        width: height

        anchors.horizontalCenter: button.horizontalCenter
        anchors.top: edge === Qt.BottomEdge ? button.top : undefined
        anchors.bottom: edge === Qt.TopEdge ? button.bottom : undefined
        color: Style.button.color_background
    }

    transform: Translate {
        Behavior on y { NumberAnimation { } }
        y: enabled ? 0 : edge === Qt.TopEdge ? -button.height : button.height
    }
}
