import QtQuick

Item {
    id: root

    state: "sine"

    Row {
        IconButton {
            id: sineBtn
            width: root.width/4
            height: root.height
            source: "qrc:/images/icons/sine.png"
            onPressed: root.state = "sine"
        }
        IconButton {
            id: triangleBtn
            width: root.width/4
            height: root.height
            source: "qrc:/images/icons/triangle.png"
            onPressed: root.state = "triangle"
        }
        IconButton {
            id: squareBtn
            width: root.width/4
            height: root.height
            source: "qrc:/images/icons/square.png"
            onPressed: root.state = "square"
        }
        IconButton {
            id: testingBtn
            width: root.width/4
            height: root.height
            source: "qrc:/images/icons/testing.png"
            onPressed: root.state = "testing"
        }
    }

    states: [
        State {
            name: "sine"
            PropertyChanges {
                target: sineBtn
                scale: 1.0
                percentColor: 1.0
            }
            PropertyChanges {
                target: triangleBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: squareBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: testingBtn
                scale: 0.8
                percentColor: 0.3
            }
        },
        State {
            name: "triangle"
            PropertyChanges {
                target: sineBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: triangleBtn
                scale: 1.0
                percentColor: 1.0
            }
            PropertyChanges {
                target: squareBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: testingBtn
                scale: 0.8
                percentColor: 0.3
            }
        },
        State {
            name: "square"
            PropertyChanges {
                target: sineBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: triangleBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: squareBtn
                scale: 1.0
                percentColor: 1.0
            }
            PropertyChanges {
                target: testingBtn
                scale: 0.8
                percentColor: 0.3
            }
        },
        State {
            name: "testing"
            PropertyChanges {
                target: sineBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: triangleBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: squareBtn
                scale: 0.8
                percentColor: 0.3
            }
            PropertyChanges {
                target: testingBtn
                scale: 1.0
                percentColor: 1.0
            }
        }

    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                properties: "scale, percentColor"
                duration: 100
            }
        }
    ]
}
