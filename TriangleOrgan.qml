import QtQuick
import Music

Organ {
    id: root

    property real dutyCycle: 0.5
    property int decayRate: 200

    Decay {rate: decayRate; TriangleOscillator {frequency: 220; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 233; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 247; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 262; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 277; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 294; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 311; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 330; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 349; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 370; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 392; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 415; slewRatio: root.dutyCycle}}

    Decay {rate: decayRate; TriangleOscillator {frequency: 440; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 466; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 494; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 523; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 554; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 587; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 622; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 659; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 698; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 740; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 784; slewRatio: root.dutyCycle}}
    Decay {rate: decayRate; TriangleOscillator {frequency: 831; slewRatio: root.dutyCycle}}
}
