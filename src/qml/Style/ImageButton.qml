import QtQuick 2.12
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

AbstractButton {
    id: button

    width: 40
    height: 40

    property alias imageSource: image.source
    property int imagePadding: Style.image_button.padding

    contentItem: Item {
        id: button_content
        anchors.fill: parent
        anchors.margins: imagePadding

        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            visible: true
            smooth: true
            anchors.centerIn: parent

            sourceSize {
                width: parent.width
                height: parent.height
            }

            ColorOverlay {
                anchors.fill: parent
                source: parent
                color: Style.image_button.color_foreground
            }
        }
    }

    /*
    background: Rectangle {
        color: Style.image_button.color_background
    }
    */
}
