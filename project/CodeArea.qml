import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import pl.ide 1.0
Rectangle {

    function newTab(){
        let newTabInStack = Qt.createQmlObject('import QtQuick 2.0; CodeText {}', code_stack)
        let newTabButton = Qt.createQmlObject(`import QtQuick 2.0; import QtQuick.Controls 2.2; CodeTabButton {}`, code_tabs.tabs)
        newTabButton.codeText = newTabInStack;
        newTabInStack.changedSinceLastSave = false;
        code_tabs.tabs.setCurrentIndex(code_tabs.tabs.count-1);
    }

    function newTabBar(content, title){
        let newTabInStack = Qt.createQmlObject('import QtQuick 2.0; CodeText {}', code_stack)
        let newTabButton = Qt.createQmlObject(`import QtQuick 2.0; import QtQuick.Controls 2.2; CodeTabButton {}`, code_tabs.tabs)
        newTabButton.codeText = newTabInStack;
        newTabInStack.changedSinceLastSave = false;
        newTabInStack.fileContent = content;
        newTabInStack.title = title;
        code_tabs.tabs.setCurrentIndex(code_tabs.tabs.count-1);
    }

    function closeTab(){
        console.log("trying to close the tab")
        if(currentTab === null) return;
        let currIndex = code_stack.currentIndex
        let codeText = currentTab
        currentTabButton.codeText = null
        currentTab.parent = null
        codeText.destroy()
        code_tabs.tabs.removeItem(currIndex)
        if(tabCount == 0) newTab()
    }

    function getTarget() {
        return code_text.getTarget();
    }

    id: root
    property alias tabCount: code_stack.count
    property CodeText currentTab: (code_stack.currentIndex==-1) ? null : code_stack.itemAt(code_stack.currentIndex);
    property CodeTabButton currentTabButton: (code_tabs.tabs.currentIndex==-1) ? null : code_tabs.tabs.itemAt(code_tabs.tabs.currentIndex);
    property string fileContent: null;
    property string newTabBarName: null;
    TextArea {
        id:txtAr
    }

    CodeTabBar {
        id: code_tabs
        newTabBarName: root.newTabBarName
    }

    Button {
        id: code_new_tab_btn
        height: code_tabs.height
        anchors.right: parent.right


        text: qsTr("New")
        onClicked: newTab();
    }

    StackLayout{
        id: code_stack
        currentIndex: code_tabs.tabs.currentIndex
        y: code_tabs.height
        width: parent.width
        height: parent.height - code_tabs.height
        CodeText {
            id: code_text
            fileContent: root.fileContent
        }
    }

    Shortcut {
        sequence: "Ctrl+9"
        onActivated: {
            closeTab()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
