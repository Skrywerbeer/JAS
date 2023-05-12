import QtQuick
import QtQuick.Layouts

import QtQuick.Controls

import JASSView

Item {
    id: root;

    property alias label: label.text;
    property list<Plot> plots;
    property ListModel controls;

    width: ListView.view?.width ??
           200;
    height: ListView.view?.height ??
            200;
    Text {
        id: label;

        color: "turquoise";
        width: parent.width;
        height: parent.height*0.1;
        fontSizeMode: Text.VerticalFit;
        font.pointSize: 32;
        font.family: "gallant12x22";
        horizontalAlignment: Text.AlignHCenter;
    }

    Rectangle {
        id: frame;

        anchors.centerIn: root;
        width: 0.9*root.width;
        height: 0.8*root.height;

        color: "#202020";
        border {width: 2; color: "turquoise";}
        radius: Math.min(width, height)*0.05

        ColumnLayout {
            anchors.fill: frame;
            Repeater {
                id: graphRepeater;
                function update() {
                    for (let i = 0; i < graphRepeater.count; ++i) {
                        itemAt(i).update();
                    }
                }
                function syncTimeBases(to, exclude) {
                    const indicesToMove = [...(function*(exclude) {
                        for (let i = 0; i < graphRepeater.count; ++i) {
                            if (exclude && (i !== exclude))
                                yield i;
                            else
                                yield i;
                        }
                    })()];
                    for (const i of indicesToMove) {
                        const graph = itemAt(i);
                        graph.xInterval.lowerBound = to.xInterval.lowerBound;
                        graph.xInterval.upperBound = to.xInterval.upperBound;
                    }
                }
                model: root.plots;
                delegate: CardGraph {
                    plot: modelData;
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height/4;
                    Layout.margins: 10;
                    onZoomed: graphRepeater.syncTimeBases(this, index);
                    onPanned: graphRepeater.syncTimeBases(this, index);
                    onPressed: root.ListView.view.interactive = false;
                    onReleased: root.ListView.view.interactive = true;
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

//                            onValueChanged: plots[plotIndex].parent.update();
                            onValueChanged: graphRepeater.update();
                            Component.onCompleted: function() {
                                plots[model.plotIndex].input[model.name].value =
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
