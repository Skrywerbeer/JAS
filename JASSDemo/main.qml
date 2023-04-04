import QtQuick

import JASSCore
import JASSView as View;

Window {
    id: root;
    visible: true;

    width: 400;
    height: 400;

    Rectangle {
        anchors.fill: parent;
        gradient: Gradient {
            GradientStop {color: "#040404"; position: 0;}
            GradientStop {color: "black"; position: 1;}
        }
    }
    View.LineGraph {
        color: "red"
        height: root.height;
        width: root.width;
        anchors.fill: parent;
        input: SineOscillator {frequency: 100;}
        startTime: 0;
        endTime: 30;
    }
    View.LineGraph {
        color: "blue";
        height: root.height;
        width: root.width;
        anchors.fill: parent;
        input: TriangleOscillator {frequency: 100;}
        startTime: 0;
        endTime: 30;
    }
    View.LineGraph {
        id: gra;
        color: "green";
        height: root.height;
        width: root.width;
        anchors.fill: parent;
        input: SquareOscillator {frequency: 100;}
        startTime: 0;
        endTime: 30;
    }
    View.LineGraph {
        color: "purple"
        height: root.height;
        width: root.width;
        anchors.fill: parent;
        input: VCA {
            input: SineOscillator {frequency: 1000;}
            cv: SquareOscillator {frequency: 100; offset: 0.5; amplitude: 0.5;}}
        startTime: 0;
        endTime: 30;
    }
//    Loader {id: loader;}



//    GridView {
//        anchors.fill: parent;
//        anchors.leftMargin: 20;
//        model: DemoModel {}

//        cellWidth: parent.width/5;
//        cellHeight: parent.height/3;

//        delegate: Rectangle {
//            border.width: 2;
//            border.color: "black";
//            width: 0.8*GridView.view.cellWidth;
//            height: 0.8*GridView.view.cellHeight

//            Rectangle {
//                width: parent.width;
//                height: parent.height/5;
//                color: "royalblue";
//            }
//            Text {
//                anchors.horizontalCenter: parent.horizontalCenter;
//                text: model.demoName;
//            }
//            MouseArea {
//                anchors.fill: parent;
//                onClicked: function() {
//                    loader.source = model.demoQMLFile;
//                }
//            }
//        }
//    }
}
