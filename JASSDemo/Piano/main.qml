import QtQuick

import JASSCore

import "qrc:/javascript/notes.js" as Notes

Window {
	id: root

	visible: true;

    width: 600;
    height: 300;

    Rectangle {
        width: root.width;
        height: root.height;
        border.color: "white";
        border.width: 2;
//        gradient: Gradient {
//            GradientStop {position: 0; color: Colors.darkBlue;}
//            GradientStop {position: 0.5; color: Colors.black;}
//            GradientStop {position: 1; color: Colors.darkBlue;}
//        }
        color: "#202020";
    }
    Rectangle {
        id: frame;
        width: root.width*0.95;
        height: root.height*0.9;
        color: "transparent";
        border.color: "white";
        border.width: 2;
        radius: 4;
//        anchors.centerIn: keyboard;
        anchors.centerIn: parent;
    }

//    Keyboard {
//        id: keyboard;

//        notes: Notes.NOTE_TABLE.slice(48, 73);
//        width: root.width*0.9;
//        height: root.height*0.8;
//        x: (root.width - width)/2;
//        y: (root.height - height)/2;

//        onKeyPressed: function(note) {player.start(player.noteMap.get(note));}
//        onKeyReleased: function(note) {player.stop(player.noteMap.get(note));}
//    }
    Keyboard {
        id: keyboardLower;

        notes: Notes.NOTE_TABLE.slice(48, 60);
        width: root.width*0.9;
        height: root.height*0.4;
        x: (root.width - width)/2;
        y: root.height/2 - height;

        onKeyPressed: function(note) {player.start(player.noteMap.get(note));}
        onKeyReleased: function(note) {player.stop(player.noteMap.get(note));}
    }
    Keyboard {
        id: keyboardUpper;

        notes: Notes.NOTE_TABLE.slice(60, 72);
        width: root.width*0.9;
        height: root.height*0.4;
        x: (root.width - width)/2;
        y: root.height/2

        onKeyPressed: function(note) {player.start(player.noteMap.get(note));}
        onKeyReleased: function(note) {player.stop(player.noteMap.get(note));}
    }
    JASSPlayer {
        id: player;

        property var noteMap: new Map();
        function populate(notes) {
            const soundComponent = Qt.createComponent("SynthSound.qml", player);

            for (const note of notes) {
                const sound = soundComponent.createObject(player, {frequency: note.frequency});
                player.sources.push(sound);
                player.noteMap.set(note, sound)
            }
        }
        function populateFromString(qml) {
            for (const note of keyboard.notes) {
                const sound = Qt.createQmlObject(qml, player, "dynamic");
                sound.frequency = note.frequency;
                player.sources.push(sound);
                player.noteMap.set(note, sound)
            }
        }
        function clearSounds() {
            for (let i = 0; i < sources.length; ++i)
                sources[i].destroy();
        }
    }
    Component.onCompleted: function() {
//        player.populate(keyboard.notes);
        player.populate(keyboardLower.notes);
        player.populate(keyboardUpper.notes);
    }
}
