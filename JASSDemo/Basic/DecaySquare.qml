import JASSCore

Decay {
    id: root

    property real frequency: 440;
    property real dutyCycle: 0.5

    SquareOscillator {
        frequency: Constant {value: root.frequency;}
        dutyCycle: Constant {value: root.dutyCycle;}
    }
}
