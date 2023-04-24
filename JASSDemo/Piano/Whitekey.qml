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
//    color: Colors.darkBlue;
    color: "transparent";
    border.width: 4;
    border.color: "black";
    radius: 4;

    Halo {
        id: glow;
        color: "turquoise";
        glowWidth: 2;
        glowHeight: 0.2;
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
