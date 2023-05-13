import JASSCore

Patchboard {
    id: root;
    property real frequency: 440;
    output: Mixer {
        Decay {
            rate: 500;
            SquareOscillator {
                amplitude: SquareOscillator {
                    frequency: Constant {value: root.frequency*0.01;}
                    amplitude: Constant {value: 0.1;}
                    offset: Constant {value: 0.9;}
                }
                frequency: SineOscillator {
                    offset: Constant {value: root.frequency;}
                    amplitude: Exponential {
                        initial: Constant {value: 0;}
                        asymptote: Constant {value: root.frequency*0.01;}
                        timeConstant: Constant {value: 0.5;}
                    }
                    frequency: Constant {value: root.frequency/8;}
                }
                dutyCycle: SineOscillator {
                    offset: Constant {value: 0.5;}
                    amplitude: Constant {value: 0.2;}
                    frequency: Constant {value: 60;}
                }
            }
        }
    }
}
