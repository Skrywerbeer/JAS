import JASSCore

//VCA {
//    id: root

//    property real frequency: 440
//    input: Mixer {
//        SquareVCO {
//            frequency: root.frequency
//            deviation: 0.05*frequency
//            dutyCycle: 0.1
//            cv: SineOscillator {
//                frequency: 5
//                amplitude: 0.5
//                offset: 0.5
//            }
//        }

////        SquareOscillator {
////            frequency: root.frequency
////        }
////        SquareOscillator {
////            amplitude: 0.5
////            dutyCycle: 0.5
////            frequency: 2*root.frequency
////        }
////        SquareOscillator {
////            amplitude: 0.2
////            dutyCycle: 0.2
////            frequency: 3*root.frequency
////        }
//    }
//    cv: ADSR {
//        attack: 50
//        decay: 100
//        sustain: 100
//        sustainLevel: 0.8
//        release: 200
//    }
////    cv: VCA {
////        input: SineOscillator {
////            frequency: 20
////            offset: 0.9
////            amplitude: 0.1
////        }
////        cv: ADSR {
////            attack: 50
////            decay: 100
////            sustain: 100
////            sustainLevel: 0.8
////            release: 400
////        }
//////        cv: Constant {value: 1.0}
////    }
//}

//Mixer {
//    property alias frequency: osc.frequency

//    Decay {
//        input: oscSplit
//        rate: 1000

//        Splitter {
//            id: oscSplit
//            SineOscillator {
//                id: osc
//            }
//            outputCount: 2
//        }
//    }
//    Delay {
//        input: oscSplit
////        delay: (1/osc.frequency)
//        delay: 500
//    }

//}

Patchboard {
    id: root
    property real frequency: 440
    output: mixer

    Mixer {
        id: mixer
        inputs: [osc1, delay1]
    }
    SineOscillator {
        id: osc1

        frequency: root.frequency
    }
    Delay {
        id: delay1
        input: osc1
        delay: 1e6
    }

}
