import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.2 as T

MenuItem {
    id: control

    implicitWidth: 100
    implicitHeight: 40

    background:
        Rectangle {
            id: menu_background
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: control.highlighted ? Style.menu.color_highlight : 'transparent'
            radius: 2
        }

    contentItem:
        Text {
            //leftPadding: control.indicator.width
            //rightPadding: control.arrow.width
            text: control.text
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: Style.app.font_color
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

}
