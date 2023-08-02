import QtQuick 2.15
import QtQuick.Window 2.15
import ru.deka.bridges 1.0


Window {
    id: root

    width: 640
    height: 480
    visible: true

    title: qsTr("Hashiwokakero (Bridges)")


    Board {
        n_rows: logic.rowsCount
        n_cols: logic.columnsCount
    }

    BoardLogic {
        id: logic
        columnsCount: 10
        rowsCount: 10
        stepCount: 20
    }

}
