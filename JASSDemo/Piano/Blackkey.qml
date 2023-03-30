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
    color: Colors.black;
    border.width: 4;
    border.color: "black";
    radius: 4;

    Halo {
        id: glow;
        color: "tomato";
        glowWidth: 2;
        glowHeight: 0.3;
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
