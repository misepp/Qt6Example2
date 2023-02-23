import QtQuick 2.0

Text {
    id: errorMessage

    anchors {
        horizontalCenter: parent.horizontalCenter
    }
    font {
        pixelSize: 16
        bold: true
    }
    color: "red"

    ColorAnimation on color {
        from: "red"
        to: "yellow"
        duration: 500
        running: true
        loops: Animation.Infinite
    }
}
