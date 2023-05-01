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
                    clip: true;
                    xInterval.upperBound: 1;
                    yInterval.lowerBound: -1
                    plot: Plot {
                        id: plot;
                        color: "darkorange";
                        width: 2;
                    }
                }
                Text {
                    text: graph.yInterval.upperBound.toFixed(3);
                    anchors {top: parent.top}
                    x: 20;
                    color: "chartreuse";
                    font.pointSize: 12;
                }
                Text {
                    text: graph.yInterval.lowerBound.toFixed(3);
                    anchors {bottom: parent.bottom}
                    x: 20;
                    color: "chartreuse";
                    font.pointSize: 12;
                }
                Text {
                    text: graph.xInterval.lowerBound.toFixed(3);
                    anchors.verticalCenter: parent.verticalCenter;
                    x: 20;
                    color: "cyan";
                    font.pointSize: 12;
                }
                Text {
                    text: graph.xInterval.upperBound.toFixed(3);
                    anchors.verticalCenter: parent.verticalCenter;
                    x: parent.width - (contentWidth + 40);
                    color: "cyan";
                    font.pointSize: 12;
                }


                MouseArea {
                    property point lastPoint;
                    anchors.fill: parent;

                    onPressed: function(event) {
                        lastPoint = Qt.point(event.x, event.y);
                        event.accepted = true;
                        root.ListView.view.interactive = false;
                    }
                    onReleased: function(event) {
                        root.ListView.view.interactive = true;
                    }

                    onPositionChanged: function(event) {
                        event.accepted = true;

                        const xStep = graph.xInterval.width()/graph.width;
                        const yStep = graph.yInterval.width()/graph.height;
//                        if (event.button === Qt.LeftButton) {
                        const delta = Qt.point(event.x - lastPoint.x,
                                               event.y - lastPoint.y);
                        graph.xInterval.lowerBound -= delta.x*xStep;
                        graph.xInterval.upperBound -= delta.x*xStep;
                        graph.yInterval.lowerBound += delta.y*yStep;
                        graph.yInterval.upperBound += delta.y*yStep;
//                        }
                        lastPoint = Qt.point(event.x, event.y);
                    }
                }
                FitButton {
                    width: 40;
                    height: 40;
                    opacity: 0.6;
                    anchors {top: parent.top; right: parent.right}
                    onClicked: graph.autoScaleYInterval();
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
                            step: model.step;

                            onValueChanged: graph.update();
                            Component.onCompleted: function() {
                                plot.input[model.name].value =
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
