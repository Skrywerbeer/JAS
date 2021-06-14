import JASS

Decay {
    id: root

    property alias frequency: osc.frequency
    property alias dutyCycle: osc.slewRatio

    TriangleOscillator {id: osc}
}
