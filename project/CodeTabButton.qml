import QtQuick 2.0
import QtQuick.Controls 2.0

TabButton {
    id: root
    property CodeText codeText
    onCodeTextChanged: {
        if(codeText === undefined || codeText === null) return;
        if(codeText != undefined) {
            console.log('codeText of tab is not undefined!')
            text = codeText.title
        }
        codeText.titleChanged.connect(function(){
            text = codeText.title
        })
        if (codeText.textArea.text == "")   title = "untitled"
    }



}

