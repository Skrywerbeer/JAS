import QtQuick
import QtQuick.Layouts

Item {
    id: root;

    property alias from: spinBox.from;
    property alias to: spinBox.to;
    property alias value: spinBox.value;
    property alias label: label.text;

    RowLayout {
        anchors.fill: parent;

        Text {
            id: label;

            color: "ivory";
            Layout.alignment: Qt.AlignLeft;
            text: "label";
            font.pointSize: 16;
        }

        SpinBox {
            id: spinBox;

            Layout.alignment: Qt.AlignRight;
            Layout.preferredWidth: 160;
            Layout.minimumHeight: 10;
            Layout.preferredHeight: 40;

        }
    }
}
