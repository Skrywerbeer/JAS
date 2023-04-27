import QtQuick

import QtQuick.Controls

import JASSCore
import JASSView

Window {
    id: root;
    visible: true;

    width: 800;
    height: 600;

    Rectangle {
        color: "#202020";
        anchors.fill: parent;
    }
    JASSPlayer {
        id: player;
    }


    ListView {
        width: root.width;
        height: root.height;
        model: LibraryModel {}
    }

}
