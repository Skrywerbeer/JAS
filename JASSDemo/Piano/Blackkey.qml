import QtQuick

Rectangle {
    id: root;

    function press() {
        state = "pressed";
    }
    function release() {
        state = "released";
    }

    z: 1;
    color: "peru";
    border.width: 4;
    border.color: "saddlebrown";
    radius: 4;

    Halo {
        id: glow;
        color: "royalblue";
        glowHeight: 0.1;
        glowWidth: 1;
    }

    state: "released";
    states: [
        State {
            name: "released"
            PropertyChanges {target: glow; intensity: 0;}
        },
        State {
            name: "pressed"
            PropertyChanges {target: glow; intensity: 0.9;}
        }
    ]
}
