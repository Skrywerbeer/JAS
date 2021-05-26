import QtQuick

Rectangle {
    id: root

    signal pressed
    signal released

    width: 50
    height: 200
    color: "ivory"
    border {width: 2; color: "black"}
    state: "released"

    MouseArea {
        anchors.fill: parent
        onReleased: {
            root.released()
            root.state = "released"
        }
        onPressed: {
            root.pressed()
            root.state = "pressed"
        }
    }

    states: [
        State {
            name: "released"
            PropertyChanges {
                target: root
                color: "ivory"
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: root
                color: "grey"
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "*"
            ColorAnimation {
                easing.type: Easing.InQuad
                duration: 100
            }
        }

    ]
}
