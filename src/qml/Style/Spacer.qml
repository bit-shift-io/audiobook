import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2

Item {
    id: root
    height: Style.spacer.margin
    width: parent.width
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignCenter
    Rectangle {
        color: Style.spacer.color
        anchors.fill: parent
    }
}
