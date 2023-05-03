import QtQuick

Item {
    id: root;

    component AdjustButton : Rectangle {
        id: buttonRoot;

        signal clicked
        property alias label: buttonLabel.text;
        property alias pressed: buttonMouseArea.pressed;

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

    property real value: 0.5;
    property real step: 1.0;
    property real from: 0;
    property real to: 1.0;
    property color borderColor;

    function decrement() {
        const newValue = root.value - root.step;
        if (newValue >= root.from)
            root.value = newValue;
        else
            root.value = root.from;
    }
    function increment() {
        const newValue = root.value + root.step;
        if (newValue <= root.to)
            root.value = newValue;
        else
            root.value = root.to;
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
                id: valueLabel;

                anchors.fill: frame;
                color: "ivory";
                text: root.value.toFixed(2);
                font.pointSize: 32;
                font.family: "gallant12x22"
                fontSizeMode: Text.Fit;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
        }
        AdjustButton {
            id: decButton;

            height: root.height;
            width: height;
            label: "▼";

            onClicked: function() {
                if (timer.timesTriggered === 0)
                    root.decrement();
            }
        }
        AdjustButton {
            id: incButton;

            height: root.height;
            width: height;
            label: "▲";

            onClicked: function() {
                if (timer.timesTriggered === 0)
                    root.increment();
            }
        }
    }
    Timer {
        id: timer;
        property int timesTriggered: 0;

        running: false;
        interval: Math.max(1e3*Math.pow(0.5, timesTriggered), 10);
        repeat: true;
    }

    states: [
        State {
            name: "DecrementHeld";
            when: (root.state !== "AtBottom") && (decButton.pressed);
            StateChangeScript {
                script: timer.timesTriggered = 0;
            }

            PropertyChanges {
                timer {
                    running: true;
                    onTriggered: function() {
                        root.decrement();
                        timer.timesTriggered++;
                    }
                }
            }
        },
        State {
            name: "IncrementHeld";
            when: (root.state !== "AtTop") && (incButton.pressed);
            StateChangeScript {
                script: timer.timesTriggered = 0;
            }
            PropertyChanges {
                timer {
                    running: true;
                    onTriggered: function() {
                        root.increment();
                        timer.timesTriggered++;
                    }
                }
            }
        },
        State {
            name: "AtBottom";
            when: (root.value === root.from)
            PropertyChanges {
                decButton {opacity: 0;}
            }
        },
        State {
            name: "AtTop";
            when: (root.value === root.to);
            PropertyChanges {
                incButton {opacity: 0;}
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {property: "opacity"; duration: 100;}
        }

    ]
}
