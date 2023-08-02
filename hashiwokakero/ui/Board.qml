import QtQuick 2.15

Rectangle {
    id: board_base
    anchors.fill: parent

    color: "lightgrey"

    property int n_rows
    property int n_cols
    property int cell_height: parent.height/n_rows/2

    Rectangle {
        id: board
        anchors.centerIn: parent
        color: "white"
        width: parent.height
        height: parent.height

        property int selected_row
        property int selected_col

        selected_col: -1
        selected_row: -1

        Repeater {
            model: logic.bridges
            delegate: Bridge {
                required property var modelData
                first: modelData.first
                second: modelData.second
                bridge_size: modelData.size
            }
        }


        Repeater {
            model: logic.islands
            delegate: Island {
                id: this_island
                required property var modelData

                r: modelData.r
                c: modelData.c
                req: modelData.req
                rem: modelData.rem
            

                width: cell_height
                height: cell_height

                color: (modelData.r === board.selected_row && modelData.c === board.selected_col) ? "lightgrey" : "white"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (board.selected_row != -1 || board.selected_col != -1) {
                            logic.buildBridge(board.selected_row, board.selected_col, this_island.r, this_island.c)

                            board.selected_row = -1
                            board.selected_col = -1
                        } else {
                            board.selected_row = this_island.r
                            board.selected_col = this_island.c
                        }

                    }
                }
            }

        }
    }

}
