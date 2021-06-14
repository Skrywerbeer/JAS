import JASS

VCA {
    id: root

    property real frequency: 440
    input: Mixer {
        SineOscillator {
            frequency: root.frequency
        }
        SineOscillator {
            frequency: Math.pow(2, 3/12)*root.frequency
        }
        SineOscillator {
            frequency: Math.pow(2, 7/12)*root.frequency
        }
    }
    //    cv: ADSR {
    //        attack: 50
    //        decay: 100
    //        sustain: 100
    //        sustainLevel: 0.8
    //        release: 200
    //    }
    cv: VCA {
        input: SineOscillator {
            frequency: 5
            offset: 0.7
            amplitude: 0.3
        }
//        cv: ADSR {
//            attack: 50
//            decay: 100
//            sustain: 100
//            sustainLevel: 0.8
//            release: 400
//        }
        cv: Constant {value: 1.0}
    }
}
