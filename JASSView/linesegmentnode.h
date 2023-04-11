#ifndef LINESEGMENTNODE_H
#define LINESEGMENTNODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>
#include <QPointF>


class LineSegmentNode : public QSGGeometryNode {
	public:
		LineSegmentNode(const QColor &color=QColor(Qt::white));
		~LineSegmentNode();

		QPointF p1() const;
		void setP1(const QPointF &point);
		QPointF p2() const;
		void setP2(const QPointF &point);

		QColor color() const;
		void setColor(const QColor &color);

	private:
		QSGGeometry *_geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                                         2);
		QSGFlatColorMaterial *_material = new QSGFlatColorMaterial;
};


#endif // LINESEGMENTNODE_H
