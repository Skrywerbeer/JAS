import JASSCore

Decay {
    id: root

    property real frequency: 440;
    property real dutyCycle: 0.5;

    TriangleOscillator {
        frequency: Constant {value: root.frequency;}
        slewRatio: Constant {value: root.dutyCycle;}
    }
}
