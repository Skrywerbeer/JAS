import QtQuick

Item {
    id: root;

    signal runClicked(demoName: string);

    width: GridView.view?.cellWidth ??
           ListView.view?.width ??
           200;
    height: GridView.view?.cellHeight ??
            ListView.view?.height/5 ??
            200;


    Rectangle {
        id: background;

        width: root.width - 20;
        height: root.height - 20;
        anchors.centerIn: root;
        color: "#161616";
        opacity: 0.3;
        radius: 4;
    }
    Rectangle {
        id: frame;

        width: root.width - 20;
        height: root.height - 20;
        anchors.centerIn: root;
        color: "transparent";
        border {color: "cyan"; width: 4;}
        radius: 4;

        Text {
            id: label;

            x: contentHeight;
            anchors.verticalCenter: frame.verticalCenter;

            font {family: "monospace"; pointSize: 20; bold: true}
            color: "turquoise";
            text: model.demoName;
        }
        RunButton {
            id: runBtn;

            width: frame.width/9;
            height: frame.height/3;
            x: frame.width - width - 20;
            anchors.verticalCenter: frame.verticalCenter;

            onClicked: root.runClicked(model.demoEntryPoint);
        }
    }
}
