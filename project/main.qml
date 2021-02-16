
import QtQuick 2.2
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.4
import pl.ide 1.0
import Qt.labs.folderlistmodel 1.0
import QtQuick.Controls 1.5
import QtQml.Models 2.2
//import io.qt.examples.quick.controls.filesystembrowser 1.0
Window {
    visible: true
    title: qsTr("IDE code")
    height: 720
    width: 960


    //akcja otwierania
    Action {
        id: fileOpenAction
        onTriggered: {
            fileDialog.selectExisting = true
            fileDialog.open()
        }
    }

    //akcja zapisywania
    Action {

        id: fileSaveAsAction
        onTriggered: {
            fileDialog.selectExisting = false
            fileDialog.open()
          }

    }
    //wyskakujący dialog
           FileDialog {
               id: fileDialog
               //nameFilters: ["Text files (*.txt)", "HTML files (*.html, *.htm)", ""]
               onAccepted: {
                   if (fileDialog.selectExisting) {
                        document.fileUrl = fileUrl
                        document.newTabBar(document.text, document.documentTitle)
                   }
                   else
                       {
                           document.saveAs(fileUrl)
                           //document.newTabBar(document.text, document.documentTitle)
                           document.changeNameOfTabBar(document.documentTitle)
                       }
               }
           }

           Compiler {
               id: compiler
           }

           DocumentHandler {
               id: document
               function newTabBar(content, title){
                   code_area.newTabBar(content, title)
               }
                function changeNameOfTabBar(name) {
                    code_area.newTabBarName = name;
                }
           }



Column {
 id: code_main
 spacing: 0;
 anchors.fill: parent

 Rectangle {
    id: upper_menu
    width: parent.width
    height: 32
    color: 'grey'



    Button { // tym buttonem zapisujesz
        id: code_filetree_savebutton
        x: 70
        y: parent.height/2 - 15
        width: 70
        height: 30
        text: qsTr("save")
        action: fileSaveAsAction
    }

    Button { // tym buttonem otwierasz
        id: code_filetree_openbutton
        x:1
        y: parent.height/2 - 15
        width: 70
        height: 30
        text: qsTr("open file")
        action: fileOpenAction

    }

 }


 Row {
    spacing: 0
    width: parent.width
    height: parent.height - upper_menu.height - bottom_menu.height

    ItemSelectionModel {
        id: file_sel
        model: fileSystemModel
    }

            TreeView{
                id: code_filetree
                //anchors.left: parent.left
                height: parent.height
                width: 300
                model: fileSystemModel
                selection: file_sel
                selectionMode: 1
                TableViewColumn {
                    title: "Name"
                    role: "fileName"
                    resizable: false
                }
                onClicked: {
                    compiler.setFileNameAndPath(index.model, index)
                }
                onDoubleClicked: {
                    code_area.newTabBar(compiler.getFileContent(), compiler.getFileName())
                }

            }
            Rectangle {
                id: side_bar
                color: "darkgrey"
                height: parent.height
                width: 30
                Button {
                    id: code_filetree_show_button
                    x: parent.width-code_filetree_show_button.width
                    y: 5
                    width: 30
                    height: 30
                    text: qsTr("◀")
                    onClicked: function() {
                                   if(code_filetree_show_button.text=="▶"){
                                       code_filetree.width = 300
                                       code_filetree_show_button.text = "◀"
                                   } else {
                                       code_filetree_show_button.text = "▶"
                                       code_filetree.width = 0

                                   }
                               }

                }
            }
        CodeArea {
            id: code_area
            height: parent.height
            width: parent.width-code_filetree.width
        }
 }
 Rectangle {
    id: bottom_menu
    color: 'grey'
    width: parent.width
    height: 30

    TextField {
        id: compiler_output
        anchors.fill: parent
        x: bottom_bar.height
        horizontalAlignment: Text.AlignCenter
        text: compiler.output
    }
    Rectangle {
        id:bottom_bar
        color: "darkgrey"
        height: 30
        width: parent.width

        TextField {
            id: output_file
            anchors.right: bottom_menu_run_button.left
            anchors.rightMargin: 5
            width: 100
            height: 30
            horizontalAlignment: Text.AlignCenter
            placeholderText: "Output File"
        }
        TextField {
            id: run_arguments
            anchors.right: output_file.left
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            width: 100
            height: 30
            horizontalAlignment: Text.AlignCenter
            placeholderText: "Arguments"
        }
        Button {
            id: bottom_menu_compile_button
            anchors.right: bottom_menu_show_button.left
            anchors.rightMargin: 5
            width: 80
            height: 30
            text: qsTr("compile")
            onClicked: function() {
                compiler.compile(output_file.text);
            }


        }
        Button {
            id: bottom_menu_run_button
            anchors.right: bottom_menu_compile_button.left
            anchors.rightMargin: 5
            width: 40
            height: 30
            text: qsTr("run")
            onClicked: function() {
                compiler.run(run_arguments);
            }

        }
        Button {
            id: bottom_menu_show_button
            anchors.right: parent.right
            anchors.rightMargin: 5
            y: 0
            width: 30
            height: 30
            text: qsTr("▲")
            onClicked: function() {
                           if(bottom_menu_show_button.text=="▲"){
                               bottom_menu.height = 250
                               bottom_menu_show_button.text = "▼"
                           } else {
                               bottom_menu.height = 30
                               bottom_menu_show_button.text = "▲"
                           }
            }
        }
    }

 }


}

}

