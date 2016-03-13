import QtQuick 2.4

Image {
    id: image
    property alias label: title.text
    fillMode: Image.PreserveAspectFit
    opacity: enabled ? 1 : .5
    signal clicked()

    // Title:
    Text {
        id: title
        anchors.centerIn: parent
        font.pixelSize: 18
        color: "black"
    }

    // Handle clicks:
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: image.clicked()
    }

    // Pressed state:
    states: State {
        name: "pressed"
        when: mouseArea.pressed
        PropertyChanges {
            target: image
            scale: .85
        }
    }
}
