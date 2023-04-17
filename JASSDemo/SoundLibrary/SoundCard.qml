import QtQuick
import QtQuick.Controls

import JASSCore
import JASSView

Rectangle {
    id: root;

//    required property Component sound;
    property Source playedSound;
    property Item generator;

    property alias interval: graph.xInterval;

    color: "black";
    border {width: 1; color: "red";}

    Column {
        LineGraph {
            id: graph;
            width: root.width;
            height: root.height*0.4;
            padding {left: 20; right: 20; top: 20; bottom: 20;}
            verticalAxis {
                visible: true;
                majorTicks {
                    count: 5;
                    length: 20;
                }
                minorTicks {
                    count: 1;
                    color: "red";
                }
            }
            horizontalAxis {
                visible: true;
                majorTicks {
                    count: 5;
                    length: 20;
                }
                minorTicks {
                    count: 0;
                    color: "red"
                }
            }
            xInterval { lowerBound: 0; upperBound: upper.value/1000;}
            yInterval {lowerBound: -1.5; upperBound: 1.5}
            plot: Plot {
                id: plot
                width: 1.5;
                color: "blueviolet";
            }

            SpinBox {
                id: upper;
                from: 1;
                to: 2000;
                value: 500;
                editable: true;
                anchors {bottom: graph.bottom; right: graph.right;}
            }
        }
        Rectangle {
            id: frame;

            width: root.width - 10;
            height: root.height*0.6
            anchors.horizontalCenter: parent.horizontalCenter;
            color: "black";
            border {width: 2; color: "white"}
            Rectangle {
                id: playBtn;
                color: "lime";
                width: 80;
                height: 80;
                anchors {bottom: parent.bottom; right: parent.right;}

                MouseArea {
                    anchors.fill: parent;
                    onPressed: function() {
                        player.start(root.playedSound);
                    }
                    onReleased: function() {
                        player.stop(root.playedSound);
                    }
                }
            }
        }
    }

    Component.onCompleted: function() {
        frame.children.push(root.generator);
        plot.input = root.generator.create();
        root.generator.changed.connect(graph.update);
        root.playedSound = root.generator.create();
        player.sources.push(root.playedSound);
    }
}
