import QtQuick
import QtQuick.Controls

Item {
    id: root
    property string dataReading: ""
    property alias indiCatorRunning: indicator.running

    width: indicator.width
    height: indicator.height

    QtObject {
        id: d
        readonly property int dataSpaceSize: 359
        readonly property int smallerFont: 18
        readonly property int largerFont: 36
        readonly property int animationDuraion: 500
    }

    BusyIndicator {
        id: indicator
        running: false
        width: d.dataSpaceSize
        height: d.dataSpaceSize
        anchors.centerIn: parent

        Text {
            text: "Current Bitcon prize"
            anchors {
                bottom: dataText.top
                bottomMargin: 5
                horizontalCenter: parent.horizontalCenter
            }

            font {
                bold: true
                pixelSize: d.smallerFont
            }
        }

        Text {
            id: dataText

            property bool animationHelper: false

            anchors.centerIn: parent
            text: root.dataReading + "€"
            font {
                bold: true
                pixelSize: d.smallerFont
            }

            onTextChanged: animationHelper = !animationHelper

            Behavior on animationHelper {
                SequentialAnimation {

                    NumberAnimation {
                        target: dataText
                        property: "font.pixelSize"
                        duration: 500
                        easing.type: Easing.InOutQuad
                        from: d.smallerFont
                        to: d.largerFont
                    }
                    NumberAnimation {
                        target: dataText
                        property: "font.pixelSize"
                        duration: d.animationDuraion
                        easing.type: Easing.InOutQuad
                        from: d.largerFont
                        to: d.smallerFont
                    }
                }
            }
        }
    }
}
