import QtQuick

import Music

Window {
    id: root

    title: "simplePiano"
    width: 480
    height: 270
    color: "black"
    visible: true

    Keyboard {
        width: parent.width
        height: parent.height/2 - 10
        anchors.top: parent.top

        keyCount: 12
        keyColor: "tomato"
        onKeyPressed: function(index) {
            organ.start(index)
        }
        onKeyReleased: function(index) {
            organ.stop(index)
        }
    }
    Keyboard {
        width: parent.width
        height: parent.height/2 - 10
        anchors.bottom: parent.bottom

        keyCount: 12
        keyColor: "royalblue"
        onKeyPressed: function(index) {
            organ.start(index + 12)
        }
        onKeyReleased: function(index) {
            organ.stop(index + 12)
        }
    }
    Organ {
        id: organ
//        TriangleOscillator {frequency: 220; slewRatio: 0.2}
//        TriangleOscillator {frequency: 233; slewRatio: 0.2}
//        TriangleOscillator {frequency: 247; slewRatio: 0.2}
//        TriangleOscillator {frequency: 262; slewRatio: 0.2}
//        TriangleOscillator {frequency: 277; slewRatio: 0.2}
//        TriangleOscillator {frequency: 294; slewRatio: 0.2}
//        TriangleOscillator {frequency: 311; slewRatio: 0.2}
//        TriangleOscillator {frequency: 330; slewRatio: 0.2}
//        TriangleOscillator {frequency: 349; slewRatio: 0.2}
//        TriangleOscillator {frequency: 370; slewRatio: 0.2}
//        TriangleOscillator {frequency: 392; slewRatio: 0.2}
//        TriangleOscillator {frequency: 415; slewRatio: 0.2}

//        TriangleOscillator {frequency: 440; slewRatio: 0.2}
//        TriangleOscillator {frequency: 466; slewRatio: 0.2}
//        TriangleOscillator {frequency: 494; slewRatio: 0.2}
//        TriangleOscillator {frequency: 523; slewRatio: 0.2}
//        TriangleOscillator {frequency: 554; slewRatio: 0.2}
//        TriangleOscillator {frequency: 587; slewRatio: 0.2}
//        TriangleOscillator {frequency: 622; slewRatio: 0.2}
//        TriangleOscillator {frequency: 659; slewRatio: 0.2}
//        TriangleOscillator {frequency: 698; slewRatio: 0.2}
//        TriangleOscillator {frequency: 740; slewRatio: 0.2}
//        TriangleOscillator {frequency: 784; slewRatio: 0.2}
//        TriangleOscillator {frequency: 831; slewRatio: 0.2}
        DecayEffect {rate: 200; SineOscillator {frequency: 220}}
        DecayEffect {rate: 200; SineOscillator {frequency: 233}}
        DecayEffect {rate: 200; SineOscillator {frequency: 247}}
        DecayEffect {rate: 200; SineOscillator {frequency: 262}}
        DecayEffect {rate: 200; SineOscillator {frequency: 277}}
        DecayEffect {rate: 200; SineOscillator {frequency: 294}}
        DecayEffect {rate: 200; SineOscillator {frequency: 311}}
        DecayEffect {rate: 200; SineOscillator {frequency: 330}}
        DecayEffect {rate: 200; SineOscillator {frequency: 349}}
        DecayEffect {rate: 200; SineOscillator {frequency: 370}}
        DecayEffect {rate: 200; SineOscillator {frequency: 392}}
        DecayEffect {rate: 200; SineOscillator {frequency: 415}}

        DecayEffect {rate: 200; SineOscillator {frequency: 440}}
        DecayEffect {rate: 200; SineOscillator {frequency: 466}}
        DecayEffect {rate: 200; SineOscillator {frequency: 494}}
        DecayEffect {rate: 200; SineOscillator {frequency: 523}}
        DecayEffect {rate: 200; SineOscillator {frequency: 554}}
        DecayEffect {rate: 200; SineOscillator {frequency: 587}}
        DecayEffect {rate: 200; SineOscillator {frequency: 622}}
        DecayEffect {rate: 200; SineOscillator {frequency: 659}}
        DecayEffect {rate: 200; SineOscillator {frequency: 698}}
        DecayEffect {rate: 200; SineOscillator {frequency: 740}}
        DecayEffect {rate: 200; SineOscillator {frequency: 784}}
        DecayEffect {rate: 200; SineOscillator {frequency: 831}}
    }
}
