import QtQuick

Item {
    id: root


    component ModeBtn : Item {
        id: btnRoot

        signal pressed()

        property real intensity: 1.0
        property alias source: img.source
        property alias scale: img.scale

        Image {
            id: img

            anchors.fill: parent
            layer.enabled: true
            layer.effect: ShaderEffect {
                id: shader
                property real intensity: btnRoot.intensity
                fragmentShader: "qrc:/shaders/darken.frag.qsb"
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: parent.pressed()
        }
    }
    state: "sine"

    Row {
        ModeBtn {
            id: sineBtn
            width: root.width/3
            height: root.height
            source: "qrc:/images/icons/sine.png"
            onPressed: root.state = "sine"
        }
        ModeBtn {
            id: triangleBtn
            width: root.width/3
            height: root.height
            source: "qrc:/images/icons/triangle.png"
            onPressed: root.state = "triangle"
        }
        ModeBtn {
            id: squareBtn
            width: root.width/3
            height: root.height
            source: "qrc:/images/icons/square.png"
            onPressed: root.state = "square"
        }
    }

    states: [
        State {
            name: "sine"
            PropertyChanges {
                target: sineBtn
                scale: 1.0
                intensity: 1.0
            }
            PropertyChanges {
                target: triangleBtn
                scale: 0.8
                intensity: 0.3
            }
            PropertyChanges {
                target: squareBtn
                scale: 0.8
                intensity: 0.3
            }
        },
        State {
            name: "triangle"
            PropertyChanges {
                target: sineBtn
                scale: 0.8
                intensity: 0.3
            }
            PropertyChanges {
                target: triangleBtn
                scale: 1.0
                intensity: 1.0
            }
            PropertyChanges {
                target: squareBtn
                scale: 0.8
                intensity: 0.3
            }
        },
        State {
            name: "square"
            PropertyChanges {
                target: sineBtn
                scale: 0.8
                intensity: 0.3
            }
            PropertyChanges {
                target: triangleBtn
                scale: 0.8
                intensity: 0.3
            }
            PropertyChanges {
                target: squareBtn
                scale: 1.0
                intensity: 1.0
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                property: "scale"
                duration: 100
            }
        }
    ]
}
