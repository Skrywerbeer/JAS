import QtQuick
import QtQuick.Shapes

Rectangle {
    id: root;

    signal clicked();

    color: "transparent";
    border {width: 2; color: "cyan";}
    radius: Math.min(width,height)/10;

    Text {
        id: label;

        anchors.centerIn: root;
        text: "Run";
        color: "cyan";
        font {family: "monospace";}
        fontSizeMode: Text.Fit;
    }
    MouseArea {
        id: mouseArea;

        anchors.fill: root;
        onClicked: root.clicked();
    }

    state: "unlit";

    states: [
        State {
            name: "Unlit";
            when: !mouseArea.pressed;
            PropertyChanges {
                root {color: "transparent";}
                label {color: "cyan";}
            }
        },
        State {
            name: "Lit";
            when: mouseArea.pressed;
            PropertyChanges {
                root {color: "cyan";}
                label {color: "black";}
            }
        }
    ]
}
