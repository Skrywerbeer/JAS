import QtQuick

Rectangle {
    id: root;
    property color baseColor: "black";

    z: 1;
    state: "released";
//    MouseArea {
//        id: mouseArea;
//        anchors.fill: parent;

//    }

    states: [
        State {
            name: "released"
//            when: !mouseArea.pressed;
            PropertyChanges {
                root {
                color: root.baseColor;
                }
            }
        },
        State {
            name: "pressed"
//            when: mouseArea.pressed;
            PropertyChanges {
                root {
                    color: "cornflowerblue";
                }
            }
        }

    ]
}
