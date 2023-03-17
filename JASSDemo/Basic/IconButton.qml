import QtQuick

Item {
    id: root

    signal pressed()

    property real percentColor: 1.0
    property alias source: img.source
    property alias scale: img.scale

    Image {
        id: img

        anchors.fill: parent
        layer.enabled: true
        layer.effect: ShaderEffect {
            id: shader
            property real percentColor: root.percentColor
            fragmentShader: "qrc:/shaders/darken.frag.qsb"
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.pressed()
    }
}

