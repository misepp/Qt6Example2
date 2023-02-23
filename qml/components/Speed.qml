import QtQuick

Item {
    id: root

    property var dataReading

    width: cauge.sourceSize.width
    height: cauge.sourceSize.height

    QtObject {
        id: d
        readonly property int needleLocation: 24
        readonly property int transformOrigin: 226
        readonly property int fontPixelSize: 32
    }

    Image {
        id: cauge
        source: "qrc:/assets/svgBackgroundCircle.png"

        Image {
            id: topCircle
            source: "qrc:/assets/TopCircle.png"
            anchors.centerIn: parent
            Text {
                id: currentSpeed
                text: root.dataReading
                color: "white"
                font.pixelSize: d.fontPixelSize
                anchors.centerIn: parent
            }
        }
        Image {
            id: speedNumbers
            source: "qrc:/assets/SpeedTexture.png"
            anchors.centerIn: parent
        }
        Image {
            id: needle
            source: "qrc:/assets/Needle.png"
            x: d.needleLocation
            y: d.needleLocation
            transform: Rotation {
                id: speedRotation
                origin {
                    x: d.transformOrigin
                    y: d.transformOrigin
                }
                angle: 1.5 * root.dataReading - 45
                Behavior on angle {
                    SpringAnimation { duration: 500; spring: 2; damping: 0.2; modulus: 360 }
                }
            }
        }
    }
}
