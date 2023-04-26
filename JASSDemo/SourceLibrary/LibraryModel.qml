import QtQuick
import QtQuick.Controls

import JASSCore


ObjectModel {
//    ExponentialCard {}
//    SineOscillatorCard {}
    LibraryCard {
        source: Exponential {}
        controls: ListModel {
            ListElement {
                name: "initial";
                from: -10;
                to: 10;
                value: 0;
            }
            ListElement {
                name: "asymptote";
                from: -10;
                to: 10;
                value: 1;
            }
            ListElement {
                name: "timeConstant";
                from: 0;
                to: 10;
                value: 1;
            }
        }
    }
    LibraryCard {
        source: SineOscillator {}
        controls: ListModel {
            ListElement {
                name: "frequency";
                from: 1;
                to: 440;
                value: 2;
            }
            ListElement {
                name: "amplitude";
                from: 0;
                to: 1;
                value: 0.5;
            }
        }
    }
    LibraryCard {
        source: SquareOscillator {}
        controls: ListModel {
            ListElement {
                name: "frequency";
                from: 1;
                to: 440;
                value: 2;
            }
            ListElement {
                name: "amplitude";
                from: 0;
                to: 1;
                value: 0.5;
            }
            ListElement {
                name: "dutyCycle";
                from: 0;
                to: 1;
                value: 0.5;
            }
        }
    }
    LibraryCard {
        source: TriangleOscillator {}
        controls: ListModel {
            ListElement {
                name: "frequency";
                from: 1;
                to: 440;
                value: 2;
            }
            ListElement {
                name: "amplitude";
                from: 0;
                to: 1;
                value: 0.5;
            }
            ListElement {
                name: "slewRatio";
                from: 0;
                to: 1;
                value: 0.5;
            }
        }
    }
}
