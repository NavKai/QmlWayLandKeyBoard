import QtQuick 2.0

Item {
    id:root
    property color color: "#35322f"

    property string text
    property string name: value
    property string displayText : text
    property var textColor: "white"

    property bool functionKey: false

    property bool isHighlighted: false

    signal clicked()
    signal pressed()
    signal released()

    Rectangle {
        anchors.fill: parent
        radius: height / 30
        color: isHighlighted ? Qt.tint(root.color, "#801e6fa7") : root.color
        Text {
            id: txt
            color: root.textColor
            anchors.margins: parent.height / 6
            anchors.fill: parent
            fontSizeMode: Text.Fit
            font.pixelSize: height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: root.displayText
        }
        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: root.clicked()
            onPressed: root.pressed()
            onReleased: root.released()
        }
    }

    Timer {
        id: highlightTimer
        interval: 100
        running: isHighlighted
        repeat: false

        onTriggered: {
            isHighlighted = false;
        }
    }

    onPressed: {
        if(!root.functionKey)
            BackEnd.sendKeyToFocusItem(text)
        isHighlighted = true;
    }

    onReleased: {

    }
}
