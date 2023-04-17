import QtQuick
import QtQuick.Controls

import JASSCore

Rectangle {
    id: root;

    component DecaySquare : Decay {
        rate: decayRateSlider.value
        SquareOscillator {
            frequency: frequencySlider.value;
            dutyCycle: dutyCycleSlider.value
        }
    }

    property var created: [];

    signal changed();

    function create() {
        const comp = Qt.createComponent("JASSDemo.SoundLibrary", "SquareGenerator.DecaySquare");
        const properties = {
        };
        const obj = comp.createObject(root, properties);
        root.created.push(obj);
        return obj;
    }

    color: "royalblue";
    border {width: 1; color: "orange";}
    Column {
        Text {
            text: "Frequency"
            color: "white";
        }
        Slider {
            id: frequencySlider;
            from: 100;
            to: 1000;
            value: 440;
            onValueChanged: root.changed();
        }
        Text {
            text: "Duty Cycle"
            color: "white";
        }
        Slider {
            id: dutyCycleSlider;
            from: 0.1;
            to: 0.9;
            value: 0.5;
            onValueChanged: root.changed();
        }
        Text {
            text: "Decay"
            color: "white";
        }
        Slider {
            id: decayRateSlider;
            from: 100;
            to: 2000;
            value: 500;
            onValueChanged: root.changed();
        }
    }
}
