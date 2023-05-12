import JASSCore

Decay {
    id: root

    property real frequency: 440;

    SineOscillator {frequency: Constant {value: root.frequency;}}
}
