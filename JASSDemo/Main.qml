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
//        gradient: Gradient {
//            GradientStop {color: "#202020"; position: 0.0;}
//            GradientStop {color: "#202020"; position: 0.6;}
//            GradientStop {color: "magenta"; position: 1;}
//        }
        color: "#202020"
    }

    Loader {id: loader;}
    ListView {
        focus: true;
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
