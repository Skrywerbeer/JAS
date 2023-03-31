import JASSCore

Patchboard {
    id: root;
    property real frequency: 440;

    output: Mixer {
        Decay {
            rate: 500;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.1;
                    offset: 0.9;
                }
                input: SquareVCO {
                    frequency: root.frequency
                    deviation: 5;
                    cv: Decay {rate: 200; SineOscillator {frequency: root.frequency*0.01;}}
                }
            }
        }
        Decay {
            rate: 400;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.2
                    offset: 0.3;
                }
                input: TriangleVCO {
                    frequency: 2*root.frequency
                    deviation: 5;
                    slewRatio: 0.3;
                    cv: Decay {rate: 200; SineOscillator {frequency: 20;}}
                }
            }
        }
        Decay {
            rate: 200;
            VCA {
                cv: SquareOscillator {
                    frequency: root.frequency*0.01;
                    amplitude: 0.2
                    offset: 0.4;
                }
                input: TriangleVCO {
                    frequency: 3*root.frequency
                    deviation: 2;
                    cv: Decay {rate: 200; SineOscillator {frequency: 30;}}
                }
            }
        }
    }
}
