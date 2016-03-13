import QtQuick 2.4
import QtQuick.Controls 1.2

Row {
    width: label.width+searchTextField.width+searchButton.width+2*spacing
    height: _settings.headerHeight-8
    spacing: 8
    property alias title: label.text
    signal returnPressed(string searchText)
    signal searchClicked(string searchText)
    signal searchTextChanged(string searchText)

    function clearSearchText()
    {
        searchTextField.text = ""
    }

    // Title:
    Label {
        id: label
        anchors.verticalCenter: parent.verticalCenter
    }

    // Search:
    TextField {
        id: searchTextField
        anchors.verticalCenter: parent.verticalCenter
        Keys.onReturnPressed: returnPressed(searchTextField.text)
        onTextChanged: searchTextChanged(text)
    }

    // Search:
    ToolButton {
        id: searchButton
        iconSource: "qrc:/qml/icons/ico-search.png"
        anchors.verticalCenter: parent.verticalCenter
        onClicked: searchClicked(searchTextField.text)
    }
}

