import QtQuick 2.15

Rectangle {
    id: bridge
    color: "#00000000"
    border.color: "black"
    border.width: 1
    visible: true

    required property var first
    required property var second
    required property int bridge_size

    x: Math.min(first.c, second.c) * cell_height * 2 + cell_height/4
    y: Math.min(first.r, second.r) * cell_height * 2 + cell_height/4

    width: Math.abs(second.c - first.c) * cell_height * 2 + Math.pow(bridge_size, 2)
    height: Math.abs(second.r  - first.r) * cell_height * 2 + Math.pow(bridge_size, 2)


}
