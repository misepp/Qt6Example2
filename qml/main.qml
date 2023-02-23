import QtQuick
import QtQuick.Controls

import Example.Backend
import Example.Constants
import "./components" as Components

ApplicationWindow {
    id: rootWindow

    property string serverErrorMessage: ""

    width: 600
    height: 800
    visible: true
    title: "Data Window"

    Component.onCompleted: {
       sourceLoader.sourceComponent = BackEnd.dataType === Constants.SpeedData ? speed : finance
    }

    onServerErrorMessageChanged: {
        if (serverErrorMessage != "") {
            errorContainer.active = true
        }
    }

    Components.BackgroundImage {
        anchors.fill: parent
    }

    Column {
        spacing: 35
        anchors {
            topMargin: spacing
            fill: parent
        }

        Loader {
            anchors.horizontalCenter: parent.horizontalCenter
            id: sourceLoader
        }

        Components.DataList {
            id: dataList
            model: BackEnd.model
            unitText: BackEnd.dataType === Constants.SpeedData ? "km/h" : "€"
            focus: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Component {
        id: speed

        Components.Speed {
            id: speedCauge
            dataReading: BackEnd.dataReading
        }
    }

    Component {
        id: finance

        Components.Finance {
            indiCatorRunning: !errorContainer.active
            dataReading: BackEnd.dataReading
        }
    }

    Loader {
        id: errorContainer

        active: false
        source: "components/ErrorMessage.qml"
        anchors {
            top: parent.top
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
        onLoaded: errorContainer.item.text = rootWindow.serverErrorMessage
    }
}
