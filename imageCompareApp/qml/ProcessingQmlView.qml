import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    width: 256
    height: 256

    // Settings:
    Settings {
        id: _settings
    }

    // View header:
    ViewHeader {
        id: viewHeader
        width: parent.width
    }

    // Main view:
    ScrollView {
        width: parent.width
        anchors.top: viewHeader.bottom
        anchors.bottom: viewFooter.top
        ListView {
            anchors.fill: parent
            spacing: 8
            model: _imageModel
            clip: true
            delegate: ItemDelegate {
                width: parent.width
                height: 128
                rowNumber: index
            }
        }
        style: ScrollViewStyle {
            handle: Item {
                implicitWidth: 14
                implicitHeight: 26
                Rectangle {
                    color: "#424246"
                    anchors.fill: parent
                }
            }
            scrollBarBackground: Item {
                implicitWidth: 14
                implicitHeight: 26
            }
        }
    }

    // View footer:
    ViewFooter {
        id: viewFooter
        width: parent.width
        anchors.bottom: parent.bottom
    }
}

