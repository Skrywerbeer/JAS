import QtQuick
import QtQml

Rectangle {
    id: root;
    property color baseColor: "ivory";

    property var overlappingKeys: [];

    function press() {
        state = "pressed";
    }
    function release() {
        state = "released";
    }

    z: 0;
    border.width: 2;
    border.color: "gray";
    state: "released";

    layer.effect: ShaderEffect {
        width: root.width; height: root.height;
//        vertexShader: "qrc:/shaders/glow.vert.qsb";
        fragmentShader: "qrc:/shaders/glow.frag.qsb";
    }

    states: [
        State {
            name: "released"
            PropertyChanges {
                root {
                color: root.baseColor;
                layer.enabled: false;
                }
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                root {
                    color: "cornflowerblue";
                    border.color: "cornflowerblue";
                    layer.enabled: true;
                }
            }
        }
    ]
}
