import QtQuick
import QtQuick.Controls
import QtQml

FocusScope {
    id: root

    function showFirst() {
        list.positionViewAtBeginning()
    }

    function showLast() {
        list.positionViewAtEnd()
    }

    property alias model: list.model
    property string unitText: ""

    width: childrenRect.width
    height: childrenRect.height

    QtObject {
        id: d
        readonly property int generalSize: 5
        readonly property int backgroundWidth: 230
        readonly property int backgroundHeight: 180
        readonly property int listWidth: 200
        readonly property int listHeight: 160
        readonly property int listItemHeight: 50
        readonly property int listItemWidth: 200
    }

    Column {
        id: layoutColumn

        spacing: 10

        Row {
            spacing: d.generalSize
            anchors.horizontalCenter: parent.horizontalCenter

            ActionButton {
                id: btn1
                buttonText: "Show first item"
                onButtonClicked: root.showFirst()
            }

            ActionButton {
                id: btn2
                buttonText: "Show last item"
                onButtonClicked: root.showLast()
            }
        }

        Rectangle {
            id: background

            width: d.backgroundWidth
            height: d.backgroundHeight
            radius: d.generalSize
            color: "#747474FF"

            border {
                color: "black"
            }

            PropertyAnimation on color {
                id: animation

                from: "#747474"
                to: "#747474FF"
                running: false
            }

            Connections {
                target: list.model
                function onRowsInserted() {
                    background.startAnimation()
                }
            }

            function startAnimation() {
                animation.restart()
            }

            ListView {
                id: list

                anchors.centerIn: parent
                focus: true
                boundsBehavior: Flickable.StopAtBounds
                snapMode: ListView.SnapToItem
                spacing: d.generalSize
                clip: true
                width: d.listWidth
                height: d.listHeight

                add: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: "width"; from: 0; to: d.listItemWidth; duration: 100 }
                        NumberAnimation { property: "height"; from: 0; to: d.listItemHeight; duration: 100 }
                    }
                }

                delegate: Rectangle {
                    radius: d.generalSize
                    border {
                        color: "#74FF74"
                    }
                    color: "#747474"
                    width: d.listItemWidth
                    height: d.listItemHeight

                    Text {
                        id: dataText
                        anchors {
                            left: parent.left
                            leftMargin: d.generalSize * 5
                            verticalCenter: parent.verticalCenter
                        }
                        text: model.data + " " + root.unitText
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.currentIndex = index
                    }
                }

                Rectangle {
                    id: scrollbar
                    anchors.right: list.right

                    y: list.visibleArea.yPosition * list.height
                    radius: d.generalSize
                    width: d.generalSize
                    height: list.visibleArea.heightRatio * list.height
                    color: "black"
                }
            }
        }
    }
}


