import QtQuick
import QtQuick.Controls

import JASSBasicDemo

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
                    height: width/4
                    onStateChanged: {
                        switch (state) {
                        case ("sine"):
                            organ.initSines()
                            break
                        case ("triangle"):
                            organ.initTriangles()
                            break
                        case ("square"):
                            organ.initSquares()
                            break
                        case ("testing"):
                            organ.initTestbed();
                            break
                        default:
                            console.log("Invalid state");
                            Qt.quit()
                        }
                    }
                }
                PlaybackControl {
                    id: playbackControls
                    width: 300
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
            organ.start(index)
        }
        onKeyReleased: function(index) {
            organ.stop(index)
        }
    }
    Keyboard {
        width: parent.width
        height: parent.height/2 - 10
        anchors.bottom: parent.bottom

        keyCount: 12
        keyColor: "royalblue"
        onKeyPressed: function(index) {
            organ.start(index + 12)
        }
        onKeyReleased: function(index) {
            organ.stop(index + 12)
        }
    }
    DynamicOrgan {
        id: organ

        dutyCycle: dutySlider.value
        decayRate: decaySlider.value
        recording: playbackControls.record
        playbackLast: playbackControls.play
        Component.onCompleted: initSines()
    }
}
