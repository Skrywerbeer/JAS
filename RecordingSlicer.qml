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
            width: 10
            height: root.height
            color: "steelblue"
            opacity: 0.5

            Rectangle {
                width: 1
                height: parent.height
                color: "red"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            DragHandler {
                id: startDrag
                yAxis.enabled: false
                xAxis {minimum: 0; maximum: root.width - startHandle.width/2}
            }
            Binding {
                target: loader.item.lastRecording
                property: "startingIndex"
//                when: startDrag.active
                value: (startHandle.x/root.width)*loader.item.lastRecording.sampleCount
            }
        }
        Rectangle {
            id: endHandle
            width: 10
            height: root.height
            color: "firebrick"
            opacity: 0.5

            Rectangle {
                width: 1
                height: parent.height
                color: "red"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            DragHandler {
                id: endDrag
                yAxis.enabled: false
                xAxis {minimum: 0; maximum: root.width - endHandle.width/2}
            }
            Binding {
                target: loader.item.lastRecording
                property: "endingIndex"
//                when: endDrag.active
                value: (endHandle.x/root.width)*loader.item.lastRecording.sampleCount
            }
        }
    }
}
