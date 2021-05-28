import QtQuick

import Music

Window {
    id: root

    title: "simplePiano"
    width: keys.childrenRect.width
    height: keys.childrenRect.height
    color: "black"
    visible: true

    Row {
        id: keys
        Repeater {
            model: 12
            BasicKey {
                onPressed: organ.start(index)
                onReleased: organ.stop(index)
            }
        }
    }

    Organ {
        id: organ
        SineGenerator {frequency: 440}
        SineGenerator {frequency: 466}
        SineGenerator {frequency: 494}
        SineGenerator {frequency: 523}
        SineGenerator {frequency: 554}
        SineGenerator {frequency: 587}
        SineGenerator {frequency: 622}
        SineGenerator {frequency: 659}
        SineGenerator {frequency: 698}
        SineGenerator {frequency: 740}
        SineGenerator {frequency: 784}
        SineGenerator {frequency: 831}
    }
}
