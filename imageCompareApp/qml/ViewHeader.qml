import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Column {
    width: parent.width
    height: 3*_settings.headerHeight
    property int cellWidth: (width-12)/_imageModel.nCols

    // Dir name:
    Item {
        width: parent.width
        height: _settings.headerHeight
        Rectangle {
            anchors.fill: parent
            anchors.margins: 4
            color: "lightgreen"
            CheckBox {
                id: showOverlay
                text: qsTr("Show Overlay")
                anchors.left: parent.left
                anchors.leftMargin: 4
                anchors.verticalCenter: parent.verticalCenter
                checked: _controller.showOverlay
                onClicked: _controller.showOverlay = checked
            }

            // Universe name:
            Text {
                anchors.centerIn: parent
                text: _reportProblemOnly ? qsTr("Cross-Directory Problems") : _controller.dirName
                font.pixelSize: 24
            }

            // Search widget:
            SearchWidget {
                id: searchWidget
                anchors.right: parent.right
                anchors.rightMargin: 4
                anchors.verticalCenter: parent.verticalCenter
                title: qsTr("Search in current view: ")
                onReturnPressed: _controller.filterCurrentView(searchText)
                onSearchClicked: _controller.filterCurrentView(searchText)
                onSearchTextChanged: _controller.filterCurrentView(searchText)
                function onProcessingFinished()
                {
                    searchWidget.clearSearchText()
                    _controller.filterCurrentView("")
                }
                Component.onCompleted: _controller.processingFinished.connect(onProcessingFinished)
            }
        }
    }

    // Exclusive group:
    ExclusiveGroup {
        id: exclusive
    }

    // Filters:
    Item {
        width: parent.width
        height: _settings.headerHeight
        Rectangle {
            anchors.fill: parent
            anchors.margins: 4
            color: "lightblue"
            RowLayout {
                Layout.preferredWidth: parent.width/2
                height: parent.height
                anchors.centerIn: parent
                spacing: 16
                Repeater {
                    model: _controller.filterMgr.nFilters()
                    RadioButton {
                        id: radioButton
                        property string text: _controller.filterMgr.filterLabel(index) + "(0)"
                        property string textColor: "black"
                        enabled: _reportProblemOnly ? _controller.filterMgr.reportProblem(index) : true
                        exclusiveGroup: exclusive
                        checked: index === _controller.activeFilter
                        style: RadioButtonStyle {
                            id: radioButtonStyle
                            label: Label {
                                color: control.enabled ? radioButton.textColor : "gray"
                                text: radioButton.text
                                font.bold: true
                            }
                        }

                        // Handle clicks:
                        onClicked: {
                            searchWidget.clearSearchText()
                            _controller.filterCurrentView("")
                            _controller.activeFilter = index
                            _controller.applyCurrentFilter()
                        }

                        // Filter status changed:
                        function onFilterStatusChanged()
                        {
                            enabled = _reportProblemOnly ? _controller.filterMgr.reportProblem(index) : true
                            var filterStatus = _controller.getFilterStatus(index)
                            var filterReportProblem = _controller.filterReportProblem(index)
                            radioButton.text = _controller.filterMgr.filterLabel(index) + " (" + filterStatus + ")"
                            radioButton.textColor = (filterStatus > 0) ?
                                (filterReportProblem ? "red" : "blue") : "black"
                        }
                        Component.onCompleted: _controller.filterStatusChanged.connect(onFilterStatusChanged)
                    }
                }

                // Problem only:
                RadioButton {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Problem Only")
                    visible: !_reportProblemOnly
                    exclusiveGroup: exclusive
                    onClicked: {
                        _controller.activeFilter = -2
                        _controller.applyCurrentFilter()
                    }
                    style: RadioButtonStyle {
                        label: Label {
                            color: "black"
                            text: control.text
                            font.bold: true
                        }
                    }
                }

                // Any:
                RadioButton {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Any")
                    exclusiveGroup: exclusive
                    checked: true
                    onClicked: {
                        _controller.activeFilter = -1
                        _controller.applyCurrentFilter()
                    }
                    style: RadioButtonStyle {
                        label: Label {
                            color: "black"
                            text: control.text
                            font.bold: true
                        }
                    }
                }

                // Spacer:
                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }

    // Column labels:
    Item {
        width: parent.width
        height: _settings.headerHeight
        Rectangle {
            anchors.fill: parent
            color: "white"
            Row {
                width: parent.width
                height: _settings.headerHeight
                Repeater {
                    model: _imageModel.nCols
                    Item {
                        width: cellWidth
                        height: _settings.headerHeight

                        Rectangle {
                            id: src
                            color: "pink"
                            width: parent.width-8
                            height: parent.height-8
                            anchors.centerIn: parent
                            border.color: "black"

                            Text {
                                color: "black"
                                anchors.centerIn: parent
                                font.pixelSize: 18
                                text: _imageModel.getDirName(index) + " (" + _imageModel.getDirId(index) + ")"
                                function onFilterStatusChanged()
                                {
                                    if (typeof(_imageModel) !== "undefined")
                                        text = _imageModel.getDirName(index) + " (" + _imageModel.getDirId(index) + ")"
                                }
                                Component.onCompleted: _controller.filterStatusChanged.connect(onFilterStatusChanged)
                            }
                        }
                    }
                }
            }
        }
    }
}

