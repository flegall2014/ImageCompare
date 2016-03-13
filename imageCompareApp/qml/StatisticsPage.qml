import QtQuick 2.4
import "../js/QChart.js" as Charts

Item {
    width: 1024
    height: 768
    property int max: 0
    property variant chartPieData: []
    property variant chartPieInfo: []
    property int legendWidth: 224
    property string currentNodeFullRelativePath: ""

    // Title:
    Text {
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 24
        text: qsTr("Quick Statistics for: " + currentNodeFullRelativePath)
    }

    // Chart:
    Chart {
        id: chart_pie
        width: parent.width/1.5
        height: parent.height/1.5
        anchors.centerIn: parent
        chartAnimated: true;
        chartAnimationEasing: Easing.Linear
        chartAnimationDuration: 0
        chartType: Charts.ChartType.DOUGHNUT
    }

    // Legend:
    Rectangle {
        border.color: "brown"
        width: legendWidth
        height: parent.height*.9
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        ListView {
            id: legend
            orientation: Qt.Vertical
            anchors.fill: parent
            clip: true
            interactive: false
            delegate: Item {
                width: legendWidth
                height: 64
                Rectangle {
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    anchors.verticalCenter: parent.verticalCenter
                    width: 48
                    height: 16
                    color: modelData.color
                }
                Text {
                    anchors.right: parent.right
                    anchors.rightMargin: 4
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: modelData.label + " (" + modelData.count + ")"
                }
            }
        }
    }

    Text {
        id: noData
        anchors.centerIn: parent
        color: "red"
        font.pixelSize: 48
        font.bold: true
        visible: false
        text: qsTr("NO DATA AVAILABLE")
    }

    // Update statistics:
    function onUpdateQuickStatistics()
    {
        updateChart()
        chart_pie.repaint()
    }

    // Update statistics:
    function onRepaintChart()
    {
        chart_pie.repaint()
    }

    // Update chart:
    function updateChart()
    {
        // Erase chart pie:
        chartPieData = []
        chartPieInfo = []

        var max = 0
        for (var i=0; i<_controller.filterMgr.nFilters(); i++)
            if ( _controller.getFilterStatus(i) > max)
                max = _controller.getFilterStatus(i)

        var colorIndex = 0
        for (var i=0; i<_controller.filterMgr.nFilters(); i++)
        {
            var filterStatus = _controller.getFilterStatus(i)
            if (filterStatus < 1)
                continue
            var angle = (filterStatus/max)*360
            var currentColor = _controller.getFilterColor(i)
            chartPieData.push({value: angle, color: currentColor})
            chartPieInfo.push({label: _controller.filterMgr.filterLabel(i), color: currentColor, count: filterStatus})
            colorIndex++
        }

        // Set chart data:
        chart_pie.chartData = chartPieData

        // Set chart legend:
        legend.model = chartPieInfo

        // Set current node full relative path:
        currentNodeFullRelativePath = _controller.currentNodeFullRelativePath()

        // No data?
        noData.visible = (chartPieData.length === 0)
    }

    Component.onCompleted: {
        // Listen to current tab changed:
        _controller.processingFinished.connect(onUpdateQuickStatistics)
        _controller.currentTabChanged.connect(onRepaintChart)
    }
}

