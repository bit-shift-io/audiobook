import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2

Item {
    id: control
    implicitHeight: Style.separator.height
    width: parent.width
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignCenter
    Rectangle {
        color: Style.separator.color
        anchors.fill: parent
    }
}
