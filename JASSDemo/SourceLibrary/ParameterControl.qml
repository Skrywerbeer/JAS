import QtQuick
import QtQuick.Layouts

Item {
    id: root;

    property alias from: spinBox.from;
    property alias to: spinBox.to;
    property alias value: spinBox.value;
    property alias step: spinBox.step;
    property alias label: label.text;

    RowLayout {
        anchors.fill: parent;

        Text {
            id: label;

            Layout.alignment: Qt.AlignLeft;
            Layout.preferredWidth: parent.width/2;

            color: "ivory";
            text: "label";
            font.pointSize: 16;
            font.family: "gallant12x22";
            fontSizeMode: Text.Fit;
        }

        SpinBox {
            id: spinBox;

            Layout.alignment: Qt.AlignRight;
            Layout.preferredWidth: parent.width/2;
            Layout.minimumWidth: 160;
            Layout.minimumHeight: 10;
            Layout.preferredHeight: parent.height;
//            Layout.preferredHeight: 40;

        }
    }
}
