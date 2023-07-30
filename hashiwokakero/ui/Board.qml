import QtQuick 2.15

Rectangle {
    anchors.fill: parent

    color: "lightgrey"

    property int n_rows
    property int n_cols
    property int cell_height: parent.height/n_rows

    Rectangle {
        anchors.centerIn: parent
        color: "grey"
        width: parent.height
        height: parent.height


        Repeater {
            model: logic.islands
            delegate: Island {
                required property var modelData
                x: modelData.c * cell_height
                y: modelData.r * cell_height
                req: modelData.req

                width: cell_height
                height: cell_height
            }

        }
    }

}
