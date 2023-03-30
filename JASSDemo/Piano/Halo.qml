import QtQuick

Rectangle {
    id: root;

    property real glowWidth: 0;
    property real glowHeight: 0;
    property real intensity: 1;

    anchors.fill: parent;
    layer.enabled: true;
    layer.effect: ShaderEffect {
        property size scale: Qt.size(1 + root.glowWidth, 1 + root.glowHeight);
        property real intensity: root.intensity;

        width: root.width;
        height: root.height;

        vertexShader: "qrc:/shaders/glow.vert.qsb";
        fragmentShader: "qrc:/shaders/glow.frag.qsb";
    }
}
