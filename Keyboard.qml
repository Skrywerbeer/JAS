import QtQuick

Item {
    id: root

    signal keyPressed(int index)
    signal keyReleased(int index)

    property int keyCount: 12
    MultiPointTouchArea {
        function scanKeyPress(touchPoints) {
            for (let i = 0; i < keys.children.length-1; ++i) {
                let child = keys.children[i]
                for (let point of touchPoints) {
                    const mapped = child.mapFromItem(root, point.x, point.y)
                    if (child.contains(Qt.point(mapped.x, mapped.y))) {
                        root.keyPressed(i)
                        child.state = "pressed"
                    }
                }
            }
        }
        function scanKeyRelease(touchPoints) {
            for (let i = 0; i < keys.children.length-1; ++i) {
                let child = keys.children[i]
                for (let point of touchPoints) {
                    const mapped = child.mapFromItem(root, point.x, point.y)
                    if (child.contains(Qt.point(mapped.x, mapped.y))) {
                        root.keyReleased(i)
                        child.state = "released"
                    }
                }
            }
        }
        function scanKeyUpdate(touchPoints) {
            for (let i = 0; i < keys.children.length-1; ++i) {
                let child = keys.children[i]
                let containsPoint = false
                for (let point of touchPoints) {
                    const mapped = child.mapFromItem(root, point.x, point.y)
                    if (child.contains(Qt.point(mapped.x, mapped.y)))
                        containsPoint = true
                }
                if (containsPoint) {
                    root.keyPressed(i)
                    child.state = "pressed"
                }
                else {
                    root.keyReleased(i)
                    child.state = "released"
                }
            }
        }

        anchors.fill: parent
        maximumTouchPoints: 10
        onPressed: function(touchPoints) {scanKeyPress(touchPoints)}
        onReleased: function(touchPoints) {scanKeyRelease(touchPoints)}
        onUpdated: function(touchPoints) {scanKeyUpdate(touchPoints)}
    }

    Row {
        id: keys
        Repeater {
            id: rep
            model: root.keyCount
            BasicKey {
                width: root.width/keyCount
                height: root.height
                onPressed: root.keyPressed(index)
                onReleased: root.keyReleased(index)
            }
        }
    }

}
