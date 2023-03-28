import JASSCore

PatchBoard {
    id: root;
    property real frequency: 440;

    output: Mixer {
        Decay {
            rate: 800;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.3
                    offset: 0.7;
                }
                input: SineVCO {
                    frequency: root.frequency
                    deviation: 5;
                    cv: Decay {rate: 200; SineOscillator {frequency: 10;}}
                }
            }
        }
        Decay {
            rate: 400;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.3
                    offset: 0.7;
                }
                input: SquareVCO {
                    frequency: 2*root.frequency
                    deviation: 10;
                    cv: Decay {rate: 200; SineOscillator {frequency: 20;}}
                }
            }
        }
        Decay {
            rate: 200;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.6
                    offset: 0.4;
                }
                input: SineVCO {
                    frequency: 3*root.frequency
                    deviation: 10;
                    cv: Decay {rate: 200; SineOscillator {frequency: 30;}}
                }
            }
        }
    }
}
