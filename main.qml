import QtQuick
import QtQuick.Controls

import Music

Window {
    id: root

    title: "simplePiano"
    width: 480
    height: 270
    color: "black"
    visible: true
    Drawer {
        id: controlDrawer
        width: parent.width
        edge: Qt.BottomEdge
        background: Rectangle {
            color: "black"
            opacity: 0.6
        }
        Row {
            Column {
                ModeSelector {
                    id: selector
                    width: 300
                    height: width/3
                    onStateChanged: {
                        switch (state) {
                        case ("sine"):
                            loader.source = "qrc:/qml/SineOrgan.qml"
                            break
                        case ("triangle"):
                            loader.source = "qrc:/qml/TriangleOrgan.qml"
                            break
                        case ("square"):
                            loader.source = "qrc:/qml/SquareOrgan.qml"
                            break
                        default:
                            console.log("Invalid state");
                            Qt.quit()
                        }
                        loader.item.dutyCycle = dutySlider.value
                        loader.item.decayRate = decaySlider.value
                    }
                }
                PlaybackControl {
                    id: playbackControls
                    width: 100
                    height: width/2
                }
            }
            Column {
                Text {
                    color: "white"
                    text: "duty cycle: " + dutySlider.value.toPrecision(2)
                }
                Slider {
                    id: dutySlider
                    enabled: ((selector.state === "triangle") || (selector.state === "square")) ? true : false
                    width: controlDrawer.width - selector.width
                    from: 0.05
                    value: 0.5
                    to: 1.0
                    onValueChanged: loader.item.dutyCycle = value
                }
                Text {
                    color: "white"
                    text: "decay rate: " + decaySlider.value.toPrecision(3)
                }
                Slider {
                    id: decaySlider
                    width: controlDrawer.width - selector.width
                    from: 50
                    value: 200
                    to: 1000
                    onValueChanged: loader.item.decayRate = value
                }
            }
        }
    }
    Keyboard {
        width: parent.width
        height: parent.height/2 - 10
        anchors.top: parent.top

        keyCount: 12
        keyColor: "tomato"
        onKeyPressed: function(index) {
            loader.item.start(index)
        }
        onKeyReleased: function(index) {
            loader.item.stop(index)
        }
    }
    Keyboard {
        width: parent.width
        height: parent.height/2 - 10
        anchors.bottom: parent.bottom

        keyCount: 12
        keyColor: "royalblue"
        onKeyPressed: function(index) {
            loader.item.start(index + 12)
        }
        onKeyReleased: function(index) {
            loader.item.stop(index + 12)
        }
    }
    Loader {
        id: loader
        Binding {
            target: loader.item
            property: "recording"
            value: playbackControls.record
        }
        Binding {
            target: loader.item
            property: "playbackLast"
            value: playbackControls.play
        }
    }
}
