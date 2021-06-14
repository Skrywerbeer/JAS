import JASS

Decay {
    id: root

    property alias frequency: osc.frequency

    SineOscillator {id: osc}
}
