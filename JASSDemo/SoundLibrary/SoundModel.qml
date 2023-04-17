import QtQuick

import JASSCore

ObjectModel {
    SoundCard {
        width: ListView.view.width;
        height: ListView.view.height;
        generator: SquareGenerator {}
    }

}
