import QtQuick

import JASSCore

import "qrc:/javascript/notes.js" as Notes

Window {
	id: root

	visible: true;

    width: 600;
    height: 300;
//    SoundEditor {
//        id: editor;
//        width: root.width;
//        height: root.height*0.5;
//        onTextChanged: {
//            console.log("haha");
//            player.clearSounds();
//            player.populateFromString(editor.text);
//        }
//    }

//    ListView {
//        id: list;
//        anchors.top: root.top;
//        width: root.width;
//        height: root.height*0.5;

//        model: NoteModel {}

//        delegate: NoteDelegate {}
//    }
    Keyboard {
        id: keyboard;

        notes: Notes.NOTE_TABLE.slice(48, 73);
        anchors.top: keyboardLower.bottom;
        width: root.width;
        height: root.height*0.5;
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
        player.populate(keyboard.notes);

    }
}
