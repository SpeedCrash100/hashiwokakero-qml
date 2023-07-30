import QtQuick 2.15

Rectangle {
    anchors.fill: parent

    color: "lightgrey"

    property int n_rows
    property int n_cols
    property int cell_height: parent.height/n_rows

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



    // Grid {
    //     id: grid
    //     anchors.fill: parent
    //     anchors.centerIn: parent
    //     rows: n_rows
    //     columns: n_cols


    //     Repeater {
    //         model:  n_rows*n_cols
    //         Island {
    //             height: cell_height
    //         }
    //     }
    // }

}
