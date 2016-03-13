import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

// Filters:
Item {
    width: parent.width
    height: _settings.headerHeight
    Rectangle {
        anchors.fill: parent
        anchors.margins: 4
        color: "lightblue"

        // Create report:
        Button {
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            text: "Create Report"
            visible: _reportProblemOnly
            onClicked: _controller.createProblemReport()
        }
    }
}

