import QtQuick

Item {
    id: root

    readonly property bool record: root.state === "recording" ? true : false
    readonly property bool play: root.state === "playing" ? true : false

    state: "idle"
    Column {
        Row {
            IconButton {
                id: recordBtn
                width: root.width/4
                height: width
                source: "qrc:/images/Basic/icons/record.png"
                onPressed: {
                    root.state = root.state !== "recording" ? "recording" : "idle"
                }
            }
            IconButton {
                id: playBtn
                width: root.width/4
                height: width
                source: "qrc:/images/Basic/icons/play.png"
                onPressed: {
                    root.state = root.state !== "playing" ? "playing" : "idle"
                }
            }
        }
        RecordingSlicer {
            width: root.width
            height: root.width/4
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
