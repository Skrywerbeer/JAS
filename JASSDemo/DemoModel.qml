import QtQuick

ListModel {
    id: root;

    ListElement {
        demoName: "Basic";
        demoQMLFile: "qrc:/JASSDemo/Basic/main.qml";
    }
    ListElement {
        demoName: "Piano";
        demoQMLFile: "qrc:/JASSDemo/Piano/main.qml";
    }
    ListElement {
        demoName: "SoundLibrary";
        demoQMLFile: "qrc:/JASSDemo/SoundLibrary/main.qml";
    }
}
