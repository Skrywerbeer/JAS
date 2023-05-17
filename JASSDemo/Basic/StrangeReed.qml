import JASSCore

Amplifier {
    id: root
    property real frequency: 440
    input: Mixer {
        SquareOscillator {
            frequency: SineOscillator {
                offset: Constant {value: root.frequency;}
                amplitude: Constant {value: 0.05*frequency;}
                frequency: Constant {value: 5;}
            }
            dutyCycle: Constant {value: 0.1;}
        }
    }
    gain: ADSR {
        attack: 50
        decay: 100
        sustain: 100
        sustainLevel: 0.8
        release: 200
    }
}
