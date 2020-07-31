import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Templates 2.2 as T

Menu {
    id: control

    background: Rectangle {
        id: menu_background
        implicitWidth: 200
        implicitHeight: 40
        color: Style.menu.color_background
        radius: 2
    }
}
