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

    PointHandler {
        onActiveChanged: {
            if (active) {
                root.state = "pressed"
                root.pressed()
            }
            else {
                root.state = "released"
                root.released()
            }
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
