import QtQuick

import JASSCore
import JASSView as View;

Window {
    id: root;
    visible: true;

    width: 400;
    height: 400;

    Rectangle {
        id: background;
        anchors.fill: parent;
        gradient: Gradient {
            orientation: Gradient.Horizontal;
            GradientStop {color: "magenta"; position: 0;}
            GradientStop {color: "black"; position: 1;}
        }
    }

    Loader {id: loader;}
    ListView {
        anchors.fill: parent;
        model: DemoModel {}
        delegate: DemoDelegate {
            onRunClicked: function(demoName) {

                loader.source = demoName;
            }
        }
        spacing: 4;
//    GridView {
//        anchors.fill: parent;
//        anchors.leftMargin: 20;
//        model: DemoModel {}

//        cellWidth: parent.width/5;
//        cellHeight: parent.height/3;
//        delegate: DemoDelegate {}
    }
}
