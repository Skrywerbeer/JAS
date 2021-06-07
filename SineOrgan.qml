import QtQuick
import JASS

Organ {
    id: root

    property int decayRate: 200

    Decay {rate: decayRate; SineOscillator {frequency: 220}}
    Decay {rate: decayRate; SineOscillator {frequency: 233}}
    Decay {rate: decayRate; SineOscillator {frequency: 247}}
    Decay {rate: decayRate; SineOscillator {frequency: 262}}
    Decay {rate: decayRate; SineOscillator {frequency: 277}}
    Decay {rate: decayRate; SineOscillator {frequency: 294}}
    Decay {rate: decayRate; SineOscillator {frequency: 311}}
    Decay {rate: decayRate; SineOscillator {frequency: 330}}
    Decay {rate: decayRate; SineOscillator {frequency: 349}}
    Decay {rate: decayRate; SineOscillator {frequency: 370}}
    Decay {rate: decayRate; SineOscillator {frequency: 392}}
    Decay {rate: decayRate; SineOscillator {frequency: 415}}

    Decay {rate: decayRate; SineOscillator {frequency: 440}}
    Decay {rate: decayRate; SineOscillator {frequency: 466}}
    Decay {rate: decayRate; SineOscillator {frequency: 494}}
    Decay {rate: decayRate; SineOscillator {frequency: 523}}
    Decay {rate: decayRate; SineOscillator {frequency: 554}}
    Decay {rate: decayRate; SineOscillator {frequency: 587}}
    Decay {rate: decayRate; SineOscillator {frequency: 622}}
    Decay {rate: decayRate; SineOscillator {frequency: 659}}
    Decay {rate: decayRate; SineOscillator {frequency: 698}}
    Decay {rate: decayRate; SineOscillator {frequency: 740}}
    Decay {rate: decayRate; SineOscillator {frequency: 784}}
    Decay {rate: decayRate; SineOscillator {frequency: 831}}
}
