import QtQuick
import QtQuick.Layouts

import QtQuick.Controls

import JASSView

Item {
    id: root;

    property alias source: plot.input;
    property ListModel controls;

    width: ListView.view?.width ??
           200;
    height: ListView.view?.height ??
            200;

    Rectangle {
        id: frame;

        anchors.centerIn: root;
        width: 0.9*root.width;
        height: 0.9*root.height;

        color: "#202020";
        border {width: 2; color: "turquoise";}
        radius: Math.min(width, height)*0.05

        ColumnLayout {
            anchors.fill: frame;
            Rectangle {
                id: graphBackground;

                Layout.fillWidth: true
                Layout.preferredHeight: parent.height/3;
                Layout.margins: 10;

                color: "black";
                border {width: 1; color: "turquoise";}
                radius: Math.min(width, height)*0.05

                LineGraph {
                    id: graph;
                    anchors.fill: graphBackground;
                    xInterval.upperBound: 1;
                    yInterval.lowerBound: -1
                        plot: Plot {
                            id: plot;
                            color: "darkorange";
                            width: 2;
                        }
                }
            }
            Rectangle {
                id: controlsFrame;

                Layout.fillWidth: true;
                Layout.fillHeight: true;
                Layout.margins: 20;

                color: "transparent";
                border {width: 2; color: "turquoise";}
                radius: Math.min(width, height)*0.05

                ColumnLayout {
                    anchors.fill: parent;
                    id: controlsColumn;
                    Repeater {
                        model: root.controls;
                        delegate: ParameterControl {
                            Layout.fillWidth: true;
                            Layout.minimumHeight: 10;
                            Layout.preferredHeight: 40;
                            Layout.maximumHeight: 30;
                            Layout.fillHeight: true;
                            Layout.leftMargin: 20;
                            Layout.rightMargin: 20;


                            label: model.name;
                            from: model.from;
                            to: model.to;
                            value: model.value;

                            onValueChanged: graph.update();
                            Component.onCompleted: function() {
                                plot.input[model.name] =
                                        Qt.binding(function() {
                                            return value;
                                        });
                            }
                        }
                    }
                }
            }
        }
    }
}
