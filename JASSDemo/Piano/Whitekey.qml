import QtQuick
import QtQml

Rectangle {
    id: root;
    property color baseColor: "ivory";

    property var overlappingKeys: [];

    z: 0;
    border.width: 2;
    border.color: "gray";
    state: "released";

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
                    border.color: "cornflowerblue";
                }
            }
        }
    ]
}
