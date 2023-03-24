import QtQuick

Window {
    id: root;
    visible: true;

    width: 400;
    height: 400;

    Loader {id: loader;}

    ListModel {
        id: demoModel;

        ListElement {
            demoName: "Basic";
            demoQMLFile: "qrc:/JASSDemo/Basic/main.qml";
        }
        ListElement {
            demoName: "Piano";
            demoQMLFile: "qrc:/JASSDemo/Piano/main.qml";
        }
    }

    GridView {
        anchors.fill: parent;
        anchors.leftMargin: 20;
        model: demoModel;

        cellWidth: parent.width/5;
        cellHeight: parent.height/3;

        delegate: Rectangle {
            border.width: 2;
            border.color: "black";
            width: 0.8*GridView.view.cellWidth;
            height: 0.8*GridView.view.cellHeight

            Rectangle {
                width: parent.width;
                height: parent.height/5;
                color: "royalblue";
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter;
                text: model.demoName;
            }
            MouseArea {
                anchors.fill: parent;
                onClicked: function() {
                    loader.source = model.demoQMLFile;
                }
            }
        }
    }
}
