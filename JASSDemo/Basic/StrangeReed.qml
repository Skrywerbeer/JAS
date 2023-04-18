import JASSCore

VCA {
    id: root

    property real frequency: 440
    input: Mixer {
        SquareVCO {
            frequency: root.frequency
            deviation: 0.05*frequency
            dutyCycle: 0.1
            cv: SineOscillator {
                frequency: 5
                amplitude: 0.5
                offset: 0.5
            }
        }
    }
    cv: ADSR {
        attack: 50
        decay: 100
        sustain: 100
        sustainLevel: 0.8
        release: 200
    }
}
