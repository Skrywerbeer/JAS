import QtQuick

ListModel {
    id: root;

    ListElement {
        demoName: "Basic";
        demoQMLFile: "qrc:/qt/qml/JASSDemo/Basic/main.qml";
    }
    ListElement {
        demoName: "Piano";
        demoQMLFile: "qrc:/qt/qml/JASSDemo/Piano/main.qml";
    }
    ListElement {
        demoName: "SoundLibrary";
        demoQMLFile: "qrc:/qt/qml/JASSDemo/SoundLibrary/main.qml";
    }
}
