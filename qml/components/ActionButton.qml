import QtQuick
import QtQuick.Controls

Button {
    id: btn

    property alias buttonText: btn.text
    property int buttonRadius: 0

    signal buttonClicked()

    focusPolicy: Qt.NoFocus

    background: Rectangle {
        color: pressed ? "#7474FF" : "#747474"
        radius: buttonRadius
    }
    onClicked: buttonClicked()
}
