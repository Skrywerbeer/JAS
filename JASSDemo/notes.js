.pragma library

const PITCH_LETTERS = ["C", "D", "E", "F", "G", "A", "B"];
const SHARP = 1;
const SHARP_CHAR = "♯";
const NATURAL = 0;
const NATURAL_CHAR = "♮";
const FLAT = -1;
const FLAT_CHAR = "♭";

const C0_FREQ = 16.35;

class Note {
    constructor(octave=0,
                frequency=C0_FREQ,
                ascending={letter="C", accidental=NATURAL},
                descending={letter="C", accidental=NATURAL}) {
        this.octave = octave;
        this.frequency = frequency;
        this.ascending = ascending;
        this.descending = descending;
    }
    isNatural() {
        if (this.ascending.accidental !== NATURAL) {
            return false;
        }
        return true;
    }
}

function nextLetter(letter) {
    const index = PITCH_LETTERS.indexOf(letter);
    if (index === -1)
        throw new Error(`invalid pitch letter: ${letter}`);
    if (index === (PITCH_LETTERS.length - 1))
        return PITCH_LETTERS[0];
    else
        return PITCH_LETTERS[index + 1];
}

const NOTE_TABLE = [...(function* () {
    let counter = 0;
    for (let octave = 0; octave <= 6; octave++) {
        for (const letter of PITCH_LETTERS) {
            yield new Note(octave,
                           Math.pow(2, (counter++)/12)*C0_FREQ,
                           {letter: letter, accidental: NATURAL},
                           {letter: letter, accidental: NATURAL});
            if (letter === "B" || letter === "E")
                continue;
            yield new Note(octave,
                           Math.pow(2, (counter++)/12)*C0_FREQ,
                           {letter: letter, accidental: SHARP},
                           {letter: nextLetter(letter), accidental: FLAT});
        }
    }
    })()];

function test(parent) {
    let comp = Qt.createComponent("NoteModel.qml");
    return comp.createObject(parent, {pitchClass: "C", octave: 3});
}
