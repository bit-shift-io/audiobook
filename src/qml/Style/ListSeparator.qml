import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2

Rectangle {
    id: control
    property QtObject listView

    anchors.leftMargin: Style.app.margin
    anchors.rightMargin: Style.app.margin
    anchors.topMargin: listView.spacing / 2 - height / 2 // center in spacing
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.bottom

    implicitHeight: Style.list_separator.height
    color: Style.list_separator.color
    visible: (index !== (listView.count - 1))
}
