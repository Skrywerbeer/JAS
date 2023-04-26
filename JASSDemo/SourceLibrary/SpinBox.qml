import QtQuick

Item {
    id: root;

    property real value: 0.5;
    property real from: 0;
    property real to: 1;
    property color borderColor;

    component AdjustButton : Rectangle {
        id: buttonRoot;

        signal clicked
        property alias label: buttonLabel.text;

        radius: height*(0.1);
        border {width: 2; color: "turquoise";}

        Text {
            id: buttonLabel;
            anchors.centerIn: buttonRoot;
        }
        MouseArea {
            id: buttonMouseArea;
            anchors.fill: buttonRoot;
            onClicked: parent.clicked();
        }
        state: "Unlit";
        states: [
            State {
                name: "Unlit"
                when: !buttonMouseArea.pressed;
                PropertyChanges {
                    buttonRoot {color: "#202020";}
                    buttonLabel {color: "turquoise";}
                }
            },
            State {
                name: "Lit";
                when: buttonMouseArea.pressed;
                PropertyChanges {
                    buttonRoot {color: "turquoise";}
                    buttonLabel {color: "#202020";}
                }
            }
        ]
    }

    width: 100;
    height: 20;

    Row {
        spacing: 4;
        Rectangle {
            id: frame;
            color: "black";
            border {width: 2; color: "turquoise";}
            height: root.height;
            width: root.width - 2*(root.height + parent.spacing);
            radius: height*0.1;

            Text {
                anchors.fill: frame;
                color: "ivory";
                text: root.value.toFixed(2);
                fontSizeMode: Text.Fit;
                font.pointSize: 32;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
        }
        AdjustButton {
            height: root.height;
            width: height;
            label: "🡇";

            onClicked: function(event) {
                const newValue = root.value - (root.to - root.from)/10;
                if (newValue >= root.from)
                    root.value = newValue;
                else
                    root.value = root.from;
            }
        }
        AdjustButton {
            height: root.height;
            width: height;
            label: "🡅";

            onClicked: {
                const newValue = root.value + (root.to - root.from)/10;
                if (newValue <= root.to)
                    root.value = newValue;
                else
                    root.value = root.to;
            }
        }
    }
}
