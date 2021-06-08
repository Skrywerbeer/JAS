import QtQuick
import JASS

Item {
    id: root

    readonly property bool record: root.state === "recording" ? true : false
    readonly property bool play: root.state === "playing" ? true : false

    state: "idle"

    Row {
        IconButton {
            id: recordBtn
            width: root.width/2
            height: root.height
            source: "qrc:/images/icons/record.png"
            onPressed: {
                root.state = root.state !== "recording" ? "recording" : "idle"
            }
        }
        IconButton {
            id: playBtn
            width: root.width/2
            height: root.height
            source: "qrc:/images/icons/play.png"
            onPressed: {
                root.state = root.state !== "playing" ? "playing" : "idle"
            }
        }
        Rectangle {
            id: graphBackground
            width: parent.width/2
            height: 50
            color: "grey"

            RecordingGraph {
                anchors.fill: parent
                color: "royalblue"
                recording: loader.item.lastRecording
                Rectangle {
                    width: 1
                    height: parent.height
                    color: "tomato"
                    x: loader.item.lastRecording.progress*parent.width
                }
                Rectangle {
                    id: startHandle
                    width: 4
                    height: parent.height
                    color: "steelblue"
                    opacity: 0.5

                    Binding {
                        target: loader.item.lastRecording
                        property: "startingIndex"
                        value: (startHandle.x/graphBackground.width)*loader.item.lastRecording.sampleCount
                    }
                    DragHandler {
                        yAxis.enabled: false
                        xAxis {minimum: 0; maximum: graphBackground.width}
                    }
                }
                Rectangle {
                    id: endHandle
                    width: 4
                    height: parent.height
                    color: "firebrick"
                    opacity: 0.5

                    Binding {
                        target: loader.item.lastRecording
                        property: "endingIndex"
                        value: (endHandle.x/graphBackground.width)*loader.item.lastRecording.sampleCount
                    }
                    DragHandler {
                        yAxis.enabled: false
                        xAxis {minimum: 0; maximum: graphBackground.width}
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "idle"
            PropertyChanges {
                target: recordBtn
                percentColor: 0.2
            }
            PropertyChanges {
                target: playBtn
                percentColor: 0.2
            }
        },
        State {
            name: "recording"
            PropertyChanges {
                target: recordBtn
                percentColor: 1.0
            }
            PropertyChanges {
                target: playBtn
                percentColor: 0.2
            }
        },
        State {
            name: "playing"
            PropertyChanges {
                target: recordBtn
                percentColor: 0.2
            }
            PropertyChanges {
                target: playBtn
                percentColor: 1.0
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                property: "percentColor"
                duration: 100
            }
        }

    ]
}
