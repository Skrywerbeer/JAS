import QtQuick
import JASS

Rectangle {
    id: root

    color: "grey"

    RecordingGraph {
        anchors.fill: parent
        color: "royalblue"
        recording: loader.item.lastRecording
        Rectangle {
            width: 1
            height: parent.height
            color: "tomato"
            x: loader.item.lastRecording.progress*parent.width
        }
        Rectangle {
            id: startHandle
            width: 1
            height: root.height
            color: "red"
            Rectangle {
                width: 20
                height: width
                color: "royalblue"
                border {width: 1; color: "black"}
                anchors {horizontalCenter: parent.horizontalCenter; top: parent.top}
                DragHandler {
                    id: startDrag
                    target: startHandle
                    yAxis.enabled: false
                    xAxis {minimum: 0; maximum: endHandle.x - startHandle.width}
                }
            }
            Binding {
                target: loader.item.lastRecording
                property: "startingIndex"
                when: startDrag.active
                restoreMode: Binding.RestoreNone
                value: (startHandle.x/root.width)*loader.item.lastRecording.sampleCount
            }
        }
        Rectangle {
            id: endHandle
            width: 1
            height: root.height
            color: "red"
            Rectangle {
                width: 20
                height: width
                radius: 10
                color: "firebrick"
                border {width: 1; color: "black"}
                anchors {horizontalCenter: parent.horizontalCenter; top: parent.top}

                DragHandler {
                    id: endDrag
                    target: endHandle
                    yAxis.enabled: false
                    xAxis {minimum: startHandle.x + endHandle.width; maximum: root.width - endHandle.width/2}
                }
            }

            Binding {
                target: loader.item.lastRecording
                property: "endingIndex"
                when: endDrag.active
                restoreMode: Binding.RestoreNone
                value: (endHandle.x/root.width)*loader.item.lastRecording.sampleCount
            }
        }
    }
}
