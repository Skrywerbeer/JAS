import QtQuick

Item {
    id: root

    signal keyPressed(int index)
    signal keyReleased(int index)

    property int keyCount: 12

    Row {
        id: keys
        Repeater {
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
