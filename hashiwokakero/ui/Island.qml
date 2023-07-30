import QtQuick 2.15

Rectangle {
    id: island
    height: 128
    width: height
    radius: height/2
    border.width: height/32
    border.color: "grey"

    required property int req;

    Text {
        id: textValue
        text: parseInt(req)
        anchors.fill: parent
        font.pixelSize: island.height/2
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}