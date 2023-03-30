import QtQuick
import QtQml

Rectangle {
    id: root;

    function press() {
        state = "pressed";
    }
    function release() {
        state = "released";
    }

    z: 0;
    color: "burlywood";
    border.width: 4;
    border.color: "saddlebrown";
    radius: 4;

    Halo {
        id: glow;
        glowWidth: 1;
        color: "royalblue";
        glowHeight: 0.1;
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
