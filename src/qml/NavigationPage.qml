import QtQuick 2.7
import QtQuick.Layouts 1.2
import "Style"

ColumnLayout {
    id: column_layout
    width: parent.width

    Button {
        text: "Settings"
        implicitWidth: parent.width
        onClicked: {
            stack_view.push("SettingsPage.qml");
            drawer.close();
        }
    }

    Button {
        text: "Exit"
        implicitWidth: parent.width
        onClicked: {
            stack_view.pop();
            drawer.close();
            Qt.quit();
        }
    }
}
