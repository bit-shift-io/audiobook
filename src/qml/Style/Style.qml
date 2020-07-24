pragma Singleton
import QtQuick 2.0
import QtQuick.Controls.Material 2.4
import QSettings 1.0

QtObject {
    // load from settings
    property double font_scale: QSettings.value('font_scale', 100) / 100

    property QtObject app: QtObject {
        property color color: '#1b2634'
        property color color_2: '#161f2b'
        property color color_highlight: '#46566b'
        property int margin: 10
        property color font_color: '#ffffff'
        property color font_color_2: '#d1d4c3'
        property string font_family: Qt.application.font.family
        property int font_size: Qt.application.font.pixelSize * font_scale
        property int font_weight: Qt.application.font.weight
    }

    property QtObject shadow: QtObject {
        property color color: '#333333'
        property int radius: 4
        property int samples: 10
    }

    property QtObject panel: QtObject {
        property color color: '#464646'
        property int radius: 0
        property int margin: app.margin
        property int margin_internal: 4
    }

    property QtObject drawer: QtObject {
        property color color: app.color
    }

    property QtObject divider: QtObject {
        property color color: '#828282'
        property int radius: 2
        property int margin: 4
    }

    property QtObject button: QtObject {
        property color color_background: '#464646'
        property color color_down: '#646464'
    }

    property QtObject slider: QtObject {
        property color color_handle: '#ffffff'
        property color color_handle_pressed: '#464646'
        property color color_background: '#464646'
        property color color_progress: '#646464'
    }

    property QtObject image_button: QtObject {
        property color color_foreground: app.font_color_2
        property color color_background: '#464646'
        property color color_down: '#646464'
        property int padding: 2
        property int padding_small: 10
    }

    property QtObject text_field: QtObject {
        property color color_background_normal: Style.app.color_2
        property color color_background_disabled: Style.app.color_2
        property color color_background_focused: Style.app.color_2
        property color color_inset_normal: color_background_normal
        property color color_inset_disabled: color_background_disabled
        property color color_inset_focused: Style.app.color_highlight
        property color font_color: Style.app.font_color
        property int font_weight: Style.app.font_weight
        property int font_size: Style.app.font_size * 1.2
    }

    property QtObject label: QtObject {

    }

    property QtObject spacer: QtObject {
        property int margin: app.margin
        property color color: '#464646'
    }

    property QtObject settings: QtObject {
        property int margin: app.margin
        property color color_background: app.color
        property int size_heading: app.font_size * 1.2
        property int weight_heading: app.font_weight + 1
    }

    property QtObject library: QtObject {
        property int margin: app.margin
        property int size_heading: app.font_size * 1.2
        property int list_spacing: 10
        property int radius_background: 0
        property color color_background: app.color_2
        property color color_highlight: app.color_highlight

    }

    property QtObject list_separator: QtObject {
        property color color: app.color
        property int height: 4
    }

    property QtObject control: QtObject {
        property int margin: app.margin
        property int font_size_title: app.font_size * 2
        property int font_size_chapter: app.font_size * 1.2
        property int spacing: 10
        property int radius_background: 0
        property color color_background: '#464646'
        property color color_highlight: app.color_highlight
    }

}
