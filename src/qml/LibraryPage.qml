import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import Library 1.0
import "Style"

Page {
    id: root_library_page

    Component.onCompleted: {
        console.log(Library.path);
    }

}
