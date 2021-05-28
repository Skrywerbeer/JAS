import QtQuick

import Music

Window {
    id: root

    title: "simplePiano"
    width: 480
    height: 270
    color: "black"
    visible: true

    Keyboard {
        anchors.fill: parent
        keyCount: organ.generatorCount
        onKeyPressed: organ.start(index)
        onKeyReleased: organ.stop(index)
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
