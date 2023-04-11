import QtQuick

import JASSCore
import JASSView

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

    LineGraph {
        id: graph;
        height: root.height;
        width: root.width;
        anchors.fill: parent;
        padding {left: 20; right: 20; top: 20; bottom: 20;}
        verticalAxis {
            position: View.Axis.Center;
            majorTicks {
                count: 10;
                length: 20;
            }
            minorTicks {
                count: 5;
                color: "blue"
            }
        }
        horizontalAxis {
            position: View.Axis.Center;
            majorTicks {
                count: 10;
                length: 20;
            }
            minorTicks {
                count: 5;
                color: "red"
            }
        }
        xInterval { lowerBound: 0; upperBound: 0.05;}
        yInterval {lowerBound: -1.5; upperBound: 1.5}

        plots: [
            Plot {
                id: plot;
                input: TriangleOscillator {frequency: 100;}
                color: "dodgerblue";
                width: 2;
                Behavior on color {ColorAnimation {duration: 300;}}
            }

        ]
    }
    Timer {
        interval: 1000;
        repeat: true;
        running: true;
        onTriggered: function() {
            plot.color = Qt.rgba(Math.random(),
                                 Math.random(),
                                 Math.random())
        }
    }
}
