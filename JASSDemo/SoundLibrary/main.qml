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
            GradientStop {color: "#442404"; position: 0;}
            GradientStop {color: "black"; position: 1;}
        }
    }
    JASSPlayer {
        id: player;
    }
    ListView {
        width: root.width;
        height: root.height;
        model: SoundModel {}
//        model: SoundsModel {}
//        delegate: SoundDelegate {}
    }
//    LineGraph {
//        id: graph;
//        anchors.fill: parent;
//        padding {left: 20; right: 20; top: 20; bottom: 20;}
//        verticalAxis {
//            majorTicks {
//                count: 10;
//                length: 20;
//            }
//            minorTicks {
//                count: 5;
//                color: "blue"
//            }
//        }
//        horizontalAxis {
//            majorTicks {
//                count: 10;
//                length: 20;
//            }
//            minorTicks {
//                count: 5;
//                color: "red"
//            }
//        }
//        xInterval { lowerBound: 0; upperBound: 0.05;}
//        yInterval {lowerBound: -1.5; upperBound: 1.5}
//        plot: Plot {
//            input: SineOscillator {frequency: 100}
//            color: "green"
//        }
//        plots: [
//            Plot {
//                input: SineOscillator {frequency: 100}
//                color: "green"
//            },
//            Plot {
//                input: SquareOscillator {frequency: 50}
//                color: "blue"
//            }

//        ]
//    }
}
