import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0
import Player 1.0
import Library 1.0
import QSettings 1.0
import 'Style'

ApplicationWindow {
    id: root
    title: {
        if (Player.titleText === '')
            Qt.application.name;
        else
            Qt.application.name + ' | ' + Player.titleText;
    }
    width: 350
    height: 500
    visible: true
    color: Style.app.color

    Settings {
        category: "window"
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    Component.onCompleted: {
        console.log('main.qml')
    }


    Drawer {
        id: drawer
        width: 0.66 * root.width
        height: root.height
        background: Rectangle {
            color: Style.drawer.color
        }

        NavigationPage {}
    }

    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: MainPage {
        }
    }
}
