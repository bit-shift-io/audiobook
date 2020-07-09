import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

import QSettings 1.0
import 'Style'

ApplicationWindow {
    id: root
    title: Qt.application.name
    width: 350
    height: 500
    visible: true
    color: Style.app.color

    property bool radar_enabled: QSettings.valueBool('radar_enabled', true)
    property var station_list: ["94672"]

    Settings {
        category: "window"
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    Component.onCompleted: {
        console.log('main.qml')
        load();
        //FileIO.clearCache();
    }

    function load() {
        station_list = QSettings.value('station_list', ["94672"]);
    }

    function save() {
        QSettings.setValue('station_list', root.station_list);
    }

    function add_station(x_wmo) {
        // for now we store a single item
        station_list[0] = x_wmo;

        /*
        // check if exists
        var is_new = true;
        for (let i in station_list) {
            if (x_wmo === station_list[i])
                is_new = false;
        }


        station_list.unshift(x_wmo);
        */

        stack_view.replace("MainPage.qml", {weather_station: station_list[0]})
        save();
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
