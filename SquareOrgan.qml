import QtQuick
import Music

Organ {
    id: root

    property real dutyCycle: 0.5
    property int decayRate: 200

    Decay {rate: decayRate; SquareOscillator {frequency: 220; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 233; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 247; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 262; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 277; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 294; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 311; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 330; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 349; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 370; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 392; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 415; dutyCycle: root.dutyCycle}}

    Decay {rate: decayRate; SquareOscillator {frequency: 440; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 466; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 494; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 523; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 554; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 587; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 622; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 659; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 698; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 740; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 784; dutyCycle: root.dutyCycle}}
    Decay {rate: decayRate; SquareOscillator {frequency: 831; dutyCycle: root.dutyCycle}}
}
