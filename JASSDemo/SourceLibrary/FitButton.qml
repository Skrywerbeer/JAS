import QtQuick

Item {
    id: root;

    signal clicked();

    Rectangle {
        anchors.fill: parent;
        border {width: 1; color: "white";}
        color: "transparent";
        radius: Math.min(width, height)*0.1;

        Image {
            anchors.fill: parent;
            source: "qrc:/images/icons/fitY.svg";
        }
        MouseArea {
            anchors.fill: parent;
            onClicked: function(event) {
                event.accepted = true;
                root.clicked();
            }
        }
    }
}
