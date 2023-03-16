import QtQuick

Rectangle {
    id: root

    state: "released"

    MouseArea {
        id: mouse;
        anchors.fill: parent;
    }

    states: [
        State {
            name: "released"
            when: !mouse.pressed;
            PropertyChanges {target: root; color: "lemonciffon"}
        },
        State {
            name: "pressed"
            when: mouse.pressed;
            PropertyChanges {target: root; color: "gray"}
        }

    ]

}
