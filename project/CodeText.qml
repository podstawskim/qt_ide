import QtQuick 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import pl.ide 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.5



Item {

    id: codeField
    //property string title : document.documentTitle // fileName z backendu cpp
    property alias text: textArea.text
    property alias textArea: textArea
    property string title: changedSinceLastSave ? "unsaved*" : "saved"
    property bool changedSinceLastSave: false
    property string fileContent: null
    LineNumbers {
        id: lineNumbers
        height: parent.height
        fillColor: "grey"
        width: 40
    }

    function getTarget() {
        return textArea;
    }

    TextArea {
        Accessible.name: "document"
        id: textArea
        x: 40
        y: 0
        width: parent.width - lineNumbers.width
        height: parent.width
        //      frameVisible: false
        activeFocusOnPress: true
        baseUrl: "qrc:/"
        focus: true

        //textFormat: Qt.RichText
        activeFocusOnTab: false
        anchors.left: lineNumbers.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        wrapMode: TextEdit.WrapAnywhere
        style: TextAreaStyle {
            backgroundColor : "grey"
        }

        onTextChanged: {
            changedSinceLastSave = true
            document.setText(textArea.text);
        }

        function update() {
            var lineHeight = 16;//(contentHeight-8) / lineCount
            lineNumbers.lineCount = lineCount
            lineNumbers.scrollY = flickableItem.contentY
            lineNumbers.lineHeight = lineHeight
            lineNumbers.cursorPosition = cursorPosition
            lineNumbers.selectionStart = selectionStart
            lineNumbers.selectionEnd = selectionEnd
            lineNumbers.text = text
            lineNumbers.update()
        }
        text: fileContent
        onLineCountChanged: update()
        onHeightChanged: update()
        onCursorPositionChanged: update()
    }

    SyntaxHighlighter {
        id: syntaxHighlighter
        textDocument: textArea.textDocument
        onHighlightBlock: {
            let rx = /\/\/.*|[A-Za-z.]+(\s*:)?|\d+(.\d*)?|'[^']*?'|"[^"]*?"/g
            let m
            while ( ( m = rx.exec(text) ) !== null ) {
                if (m[0].match(/^\/\/.*/)) {
                    setFormat(m.index, m[0].length, commentFormat);
                    continue;
                }
                if (m[0].match(/^[a-z]/)) {
                    let keywords = [ "asm",
                                    "auto",
                                    "bool",
                                    "break",
                                    "case",
                                    "catch",
                                    "char",
                                    "class",
                                    "const",
                                    "continue",
                                    "default",
                                    "delete",
                                    "do",
                                    "double",
                                    "else",
                                    "enum",
                                    "explicit",
                                    "export",
                                    "extern",
                                    "false",
                                    "float",
                                    "for",
                                    "friend",
                                    "goto",
                                    "if",
                                    "inline",
                                    "int",
                                    "long",
                                    "mutable",
                                    "namespace",
                                    "new",
                                    "operator",
                                    "private",
                                    "protected",
                                    "public",
                                    "register",
                                    "return",
                                    "short",
                                    "signed",
                                    "sizeof",
                                    "static",
                                    "struct",
                                    "switch",
                                    "template",
                                    "this",
                                    "throw",
                                    "true",
                                    "try",
                                    "typedef",
                                    "typeid",
                                    "typen8Jll8",
                                    "union",
                                    "unsigned",
                                    "using",
                                    "virtual",
                                    "void",
                                    "volatile",
                                    "while",
                                    "wchar_t"
                        ]
                    let variables = ["auto","int", "double", "unsigned","float","long","short","volatile","static","char","string"];
                    if(variables.includes(m[0])){
                        setFormat(m.index,m[0].length, variablesFormat);
                        continue;
                    }
                    if (keywords.includes(m[0])) {
                        setFormat(m.index, m[0].length, keywordFormat);
                        continue;
                    }
                    continue;
                }
                if (m[0].match(/^\d/)) {
                    setFormat(m.index, m[0].length, numberFormat);
                    continue;
                }
                if (m[0].match(/^'/)) {
                    setFormat(m.index, m[0].length, stringFormat);
                    continue;
                }
                if (m[0].match(/^"/)) {
                    setFormat(m.index, m[0].length, stringFormat);
                    continue;
                }
            }
        }



    }

    TextFormat { id: keywordFormat; textColor: "#8A2BE2" }
    TextFormat { id: numberFormat; textColor: "#0055af" }
    TextFormat { id: variablesFormat; textColor:  "#61acff"}
    TextFormat { id: stringFormat; textColor: "orange" }
    TextFormat { id: commentFormat; textColor: "orange" }

//    DocumentHandler {
//        id: document1
//        target: textArea
//    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
