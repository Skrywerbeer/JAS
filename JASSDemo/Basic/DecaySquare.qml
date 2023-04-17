import JASSCore

Decay {
    id: root

    property alias frequency: osc.frequency
    property alias dutyCycle: osc.dutyCycle

    SquareOscillator {
        id: osc
    }
}
