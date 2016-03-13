import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Rectangle {
    width: 1024
    height: 768
    color: "white"

    // Public interface:
    property int itemSpacing: 8
    property int delegateHeight: 128
    property string headerColor: "steelblue"
    property string bkgColor: "lightgray"
    property string borderColor: "black"
    property int borderWidth: 1

    // View:
    ScrollView {
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        ListView {
            id: listView
            anchors.fill: parent
            spacing: itemSpacing
            model: _searchModel
            delegate: Rectangle {
                width: parent.width
                height: delegateHeight
                color: bkgColor
                border.color: borderColor
                border.width: borderWidth
                Column {
                    anchors.fill: parent
                    anchors.margins: itemSpacing
                    spacing: itemSpacing/2
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text: "FILE: "
                        font.bold: true
                        color: "green"
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text: qmlFile
                        width: parent.width
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text: "LINE NUMBER: "
                        font.bold: true
                        color: "green"
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text: lineNumber
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text: "LINE: "
                        font.bold: true
                        color: "green"
                    }
                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: itemSpacing
                        text:  line
                    }
                }

                // Counter:
                Label {
                    anchors.right: explorerButton.left
                    anchors.rightMargin: itemSpacing
                    anchors.verticalCenter: parent.verticalCenter
                    color: "red"
                    font.pixelSize: 18
                    text: index
                }

                ToolButton {
                    id: explorerButton
                    anchors.right: parent.right
                    anchors.rightMargin: itemSpacing
                    anchors.verticalCenter: parent.verticalCenter
                    iconSource: "qrc:/qml/icons/ico-bluefolder.png"
                    onClicked: _controller.openTextEditor(qmlFile, qsTr("QML Search"), _targetString)
                }
            }
        }
    }
}
