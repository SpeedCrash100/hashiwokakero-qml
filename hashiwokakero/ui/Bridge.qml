import QtQuick 2.15

Item {
    id: bridge

    required property var first
    required property var second
    required property int bridge_size

    x: get_x()
    y: get_y()

    width: Math.abs(second.c - first.c) * cell_height * 2 + get_width()
    height: Math.abs(second.r  - first.r) * cell_height * 2 + get_width()

    Loader {
        anchors.fill: parent
        sourceComponent: (bridge_size == 2) ? side_rectangle : filled_rectangle
    }


    function get_x(): number {
        var base = Math.min(first.c, second.c) * cell_height * 2
        var offset = cell_height/2 - get_width() / 2
        return base + offset
    }

    function get_y(): number {
        var base = Math.min(first.r, second.r) * cell_height * 2
        var offset = cell_height/2 - get_width() / 2
        return base + offset
    }

    function get_width(): number {
        return Math.pow(bridge_size, 2) * cell_height / 10
    }

    Component {
        id: filled_rectangle
        Rectangle {
            color: "black"
            border.color: "black"
            border.width: 0
        }
    }

    Component {
        id: side_rectangle
        Rectangle {
            color: "#00000000"
            border.color: "black"
            border.width: get_width() / 4
        }
    }


}
