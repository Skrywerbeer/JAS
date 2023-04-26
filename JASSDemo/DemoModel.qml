import QtQuick

ListModel {
    id: root;

    ListElement {
        demoName: "Basic";
        demoEntryPoint: "qrc:/qt/qml/JASSDemo/Basic/main.qml";
        demoDescription: ""
    }
    ListElement {
        demoName: "Piano";
        demoEntryPoint: "qrc:/qt/qml/JASSDemo/Piano/main.qml";
        demoDescription: ""
    }
    ListElement {
        demoName: "SoundLibrary";
        demoEntryPoint: "qrc:/qt/qml/JASSDemo/SourceLibrary/Main.qml";
        demoDescription: ""
    }
}
