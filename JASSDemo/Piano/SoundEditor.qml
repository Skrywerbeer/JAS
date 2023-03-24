import QtQuick

import JASSDemo.Piano

Rectangle {
    id: root;

    property alias text: edit.text;

    signal editingFinished;

    gradient: Gradient {
        GradientStop {position: 0; color: "#333355";}
        GradientStop {position: 1; color: "#080808";}
    }

    Flickable {
        id: flick;
        anchors.fill: root;
        contentWidth: edit.contentWidth;
        contentHeight: edit.contentHeight;
        clip: true;

        function ensureVisible(r) {
            if (!r)
                return;
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
        }
        TextEdit {
            id: edit;
            anchors.fill: parent;
            color: "ivory";
            text: TextFile.readFile(":/JASSDemo/Piano/SynthSound.qml");
            focus: true;
            onCursorRectangleChanged: flick.ensureVisible(cursorRectangle);
            onEditingFinished: root.editingFinished();
        }
    }
}
