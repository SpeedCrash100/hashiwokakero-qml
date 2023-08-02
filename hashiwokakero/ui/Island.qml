import QtQuick 2.15

Rectangle {
    required property int req;
    required property int r;
    required property int c;
    required property int rem;

    id: island
    height: 128
    width: height
    radius: height/2
    border.width: height/32
    border.color: (rem < 0) ? "red" : "grey"

    x: c * height
    y: r * height

    Text {
        id: textValue
        text: req
        anchors.fill: parent
        font.pixelSize: island.height/2
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
