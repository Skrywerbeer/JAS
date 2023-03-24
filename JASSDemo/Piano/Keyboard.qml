import QtQuick

Item {
    id: root;

    property var notes: [];
    property var whiteKeys: [];
    property var blackKeys: [];
    property var keyMap: new Map();

    signal keyPressed(note: var);
    signal keyReleased(note: var);

    MultiPointTouchArea {
        id: touchArea;

        anchors.fill: parent;

        onReleased: function(points) {
            for (const point of points) {
                if (point.containingKey) {
                    point.containingKey.release()
                    keyReleased(root.keyMap.get(point.containingKey));
                }
            }
        }
        onTouchUpdated: function(points) {
            points.forEach((p) => {p.used = false;});
            for (const key of [...root.blackKeys, ...root.whiteKeys]) {
                for (const point of points) {
                    if (point.used) {
                        continue;
                    }
                    if (key.contains(key.mapFromItem(touchArea, point.x, point.y))) {
                        point.used = true;
                        // If this point hasn't pressed a key before.
                        if (!point.containingKey) {
                            point.containingKey = key;
                            key.press()
                            keyPressed(root.keyMap.get(key));
                        }
                        // If this point has moved to a different key.
                        if (point.containingKey && point.containingKey !== key) {
                            point.containingKey.release()
                            keyReleased(root.keyMap.get(point.containingKey));
                            point.containingKey = key;
                            key.press();
                            keyPressed(root.keyMap.get(key));
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        const whiteKeyCount = notes.reduce((count, note) => {
                                               if (note.isNatural())
                                               count++;
                                               return count;
                                           }, 0);
        const whiteComponent = Qt.createComponent("Whitekey.qml", root);
        const blackComponent = Qt.createComponent("Blackkey.qml", root);
        let x = 0;

        const blackWhiteWidthRatio = 0.5;

        let counter = 0;
        function whiteXBindingGen() {
            const current = counter;
            return function() {return (root.width/whiteKeyCount)*current;}

        }
        function blackXBindingGen() {
            const current = counter;

            return function() {
                const whiteKeyWidth = root.width/whiteKeyCount;
                return whiteKeyWidth*current - 0.5*blackWhiteWidthRatio*whiteKeyWidth;
            }
        }

        for (const note of Array.from(root.notes)) {
            let newKey;
            if (note.isNatural()) {
                const properties = {
                    width: Qt.binding(() => {return root.width/whiteKeyCount}),
                    height: Qt.binding(() => {return root.height}),
                    x: Qt.binding(whiteXBindingGen())
                };
                newKey = whiteComponent.createObject(root, properties);
                counter++;
                root.whiteKeys.push(newKey)
            }
            else {
                const properties = {
                    width: Qt.binding(() => {return (root.width/whiteKeyCount)*blackWhiteWidthRatio;}),
                    height: Qt.binding(() => {return root.height*0.66;}),
                    x: Qt.binding(blackXBindingGen())
                }

                newKey = blackComponent.createObject(root, properties);
                root.blackKeys.push(newKey)
            }
            root.keyMap.set(newKey, note);
        }
    }
}
