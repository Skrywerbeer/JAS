import QtQuick
import QtQuick.Shapes

Shape {
    id: root;

    property real miter: 0;
    property alias strokeColor: path.strokeColor;
    property alias strokeWidth: path.strokeWidth;
    property alias fillColor: path.fillColor;

    ShapePath {
        id: path;

        fillColor: "transparent";

        strokeWidth: 2;
        strokeColor: "cyan";
        strokeStyle: ShapePath.SolidLine;
        startX: 3;
        startY: 0;

        PathPolyline {
            path: [
                Qt.point(root.miter, 0),
                Qt.point(root.width - root.miter, 0),
                Qt.point(root.width, root.miter),
                Qt.point(root.width, root.height - root.miter),
                Qt.point(root.width - root.miter, root.height),
                Qt.point(root.miter, root.height),
                Qt.point(0, root.height - root.miter),
                Qt.point(0, root.miter),
                Qt.point(root.miter, 0)
            ]
        }
    }
}

