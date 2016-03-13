import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    width: parent.width
    property int cellWidth: width/_imageModel.nCols
    property int cellHeight: 128
    property int rowNumber: 0
    visible: _controller.itemVisible

    Row {
        id: row
        anchors.fill: parent
        Repeater {
            model: _imageModel.nCols

            Item {
                width: cellWidth
                height: cellHeight

                Rectangle {
                    id: src
                    color: "lightgray"
                    property int imgWidth: 0
                    property int imgHeight: 0
                    width: parent.width-8
                    height: parent.height-8
                    anchors.centerIn: parent
                    border.color: "black"

                    // Row number:
                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        text: rowNumber
                        font.bold: true
                        visible: _controller.showOverlay
                    }

                    // Image:
                    Image {
                        id: image
                        anchors.centerIn: parent
                        source: _imageModel.getImage(imageRow, index)
                        fillMode: Image.PreserveAspectFit
                        cache: true
                        onStatusChanged: {
                            if (status === Image.Ready)
                            {
                                // Set img size:
                                imgSize.text = width + "*" + height
                                if (width > src.width)
                                    width = src.width
                                if (height > src.height)
                                    height = src.height
                            }
                            else
                            if (status === Image.Error)
                                image.source = "qrc:/qml/icons/ico-corrupted.png"
                        }
                    }

                    // Picto base name:
                    Text {
                        id: pictoBaseName
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 4
                        text: _imageModel.getImageActualCasing(imageRow, index)
                        color: _settings.overlayColor
                        visible: _controller.showOverlay
                    }
                }

                // Overlay:
                Item {
                    id: overlay
                    visible: _controller.showOverlay && !_controller.isReservedPicto(image.source)
                    anchors.fill: src

                    // Image size:
                    Text {
                        id: imgSize
                        color: _settings.overlayColor
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        anchors.top: parent.top
                        anchors.topMargin: 4
                    }

                    // Image weight:
                    Text {
                        id: imgWeight
                        color: _settings.overlayColor
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        anchors.top: imgSize.bottom
                        anchors.topMargin: 4
                        text: parseFloat(_imageModel.getImageWeight(imageRow, index)/1024).toFixed(2) + " Kb"
                    }

                    // Image problems:
                    Column {
                        anchors.fill: parent
                        anchors.margins: 4
                        visible: imageProblem.length > 0
                        Repeater {
                            model: imageProblem
                            delegate: Text {
                                text: modelData
                                width: parent.width
                                color: _settings.overlayColor
                                horizontalAlignment: Text.AlignRight
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (!_controller.isReservedPicto(image.source))
                        _controller.showInExplorer(image.source)
                    }
                }

                // Search:
                ImageButton {
                    anchors.right: parent.right
                    anchors.rightMargin: 4
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 4
                    source: "qrc:/qml/icons/ico-search.png"
                    width: 32
                    onClicked: _controller.requestSearch(imageBaseName)
                    visible: _controller.showOverlay
                }
            }
        }
    }
}
