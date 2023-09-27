import QtQuick 2.0
import "."

Item {
    id:root
    width: parent.width
    height: parent.height / 3
    y:parent.height - height

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.6
    }

    signal enterPressed()

    property font font: Qt.font(
        {
            family: 'Helvetica',
            weight: Font.Normal,
            italic: false,
            pointSize: 12
        })

    KeyModel {
        id:keyModel
    }
    FontLoader {
        source: "FontAwesome.otf"
    }
    QtObject {
        id:pimpl
        property bool shiftModifier: false
        property bool symbolModifier: false
        property int verticalSpacing: 5
        property int horizontalSpacing: verticalSpacing
        property int rowHeight: root.height/4 - verticalSpacing
        property int buttonWidth:  (root.width-column.anchors.margins)/10 - horizontalSpacing
    }

    Component {
        id: keyButtonDelegate
        KeyButton {
            id: button
            width: pimpl.buttonWidth
            height: pimpl.rowHeight
            text: (pimpl.shiftModifier) ? letter.toUpperCase() : (pimpl.symbolModifier)?firstSymbol : letter
        }
    }

    Rectangle {
        id:keyboard
        color: "black"
        anchors.fill: parent;
        MouseArea {
            anchors.fill: parent
        }

        Column {
            id:column
            anchors.margins: 5
            anchors.fill: parent
            spacing: pimpl.verticalSpacing

            Row {
                height: pimpl.rowHeight
                spacing: pimpl.horizontalSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                Repeater {
                    model: keyModel.firstRowModel
                    delegate: keyButtonDelegate
                }
            }
            Row {
                height: pimpl.rowHeight
                spacing: pimpl.horizontalSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                Repeater {
                    model: keyModel.secondRowModel
                    delegate: keyButtonDelegate
                }
            }
            Item {
                height: pimpl.rowHeight
                width:parent.width
                KeyButton {
                    id: shiftKey
                    color: (pimpl.shiftModifier)? "#1e6fa7": "#1e1b18"
                    anchors.left: parent.left
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: "\uf062"
                    functionKey: true
                    onClicked: {
                        if (pimpl.symbolModifier) {
                            pimpl.symbolModifier = false
                        }
                        pimpl.shiftModifier = !pimpl.shiftModifier
                    }
                }
                Row {
                    height: pimpl.rowHeight
                    spacing: pimpl.horizontalSpacing
                    anchors.horizontalCenter:parent.horizontalCenter
                    Repeater {
                        anchors.horizontalCenter: parent.horizontalCenter
                        model: keyModel.thirdRowModel
                        delegate: keyButtonDelegate
                    }
                }
                KeyButton {
                    id: backspaceKey
                    color: "#1e1b18"
                    anchors.right: parent.right
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: "\x7F"
//                    displayText: "\uf177"
//                    inputPanel: root
//                    repeat: true
                }
            }
            Row {
                height: pimpl.rowHeight
                spacing: pimpl.horizontalSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                KeyButton {
                    id: hideKey
                    color: "#1e1b18"
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: "\uf078"
                    functionKey: true
                    onClicked: {
                        BackEnd.hideKeyBoard()
                    }
//                    showPreview: false
                }
                KeyButton {
                    color: "#1e1b18"
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: ""
//                    inputPanel: root
                    functionKey: true
                }
                KeyButton {
                    width: pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: ","
//                    inputPanel: root
                }
                KeyButton {
                    id: spaceKey
                    width: 3*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: " "
//                    showPreview: false
                }
                KeyButton {
                    width: pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: "."
                }
                KeyButton {
                    id: symbolKey
                    color: "#1e1b18"
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    text: (!pimpl.symbolModifier)? "12#" : "ABC"
                    functionKey: true
                    onClicked: {
                        if (pimpl.shiftModifier) {
                            pimpl.shiftModifier = false
                        }
                        pimpl.symbolModifier = !pimpl.symbolModifier
                    }
//                    inputPanel: root
                }
                KeyButton {
                    id: enterKey
                    color: "#1e1b18"
                    width: 1.25*pimpl.buttonWidth
                    height: pimpl.rowHeight
                    displayText: "Enter"
                    text: "\n"
                    onPressed:
                    {
                        root.enterPressed();
                    }
                }
            }
        }
    }
}
