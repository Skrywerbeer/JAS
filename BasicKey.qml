import QtQuick

Rectangle {
    id: root

    signal pressed
    signal released

    property color baseColor: "ivory"

    width: 50
    height: 200
    border {width: 2; color: "black"}
    state: "released"

    states: [
        State {
            name: "released"
            PropertyChanges {
                target: root
                color: root.baseColor
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: root
                color: Qt.darker(root.baseColor)
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
