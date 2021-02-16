import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Item {
    id: root
    width: parent.width
    property TabBar tabs: code_tabs
    property string newTabBarName: null
    height: 35

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
        TabBar {
            id: code_tabs
            y: 5
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 80
            anchors.bottomMargin: 5
            anchors.leftMargin: 0
            CodeTabButton {
                text: newTabBarName ? newTabBarName: "untitled"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:40;width:440}D{i:2}
}
##^##*/
