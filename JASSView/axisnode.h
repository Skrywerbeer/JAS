#ifndef AXISNODE_H
#define AXISNODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

#include "axis.h"

class AxisNode : public QSGNode {
	public:
		enum Orientation {
			Horizontal,
			Vertical
		};
		AxisNode(const QRectF &canvas, Orientation orientation, const Axis *axis);
		~AxisNode();

		void updateGeometry(const QRectF &canvas, const Axis *axis);
		void updateMajorTickGeometry(const QRectF &canvas, const Axis *axis);
		void updateMinorTickGeometry(const QRectF &canvas, const Axis *axis);

		void updateMaterial(const Axis *axis);
		void updateMajorTickMaterial(const Axis *axis);
		void updateMinorTickMaterial(const Axis *axis);
	private:
		const Orientation _orientation;
		QSGGeometryNode *_lineNode = new QSGGeometryNode;
		QSGGeometry *_lineGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                                         2);
		QSGFlatColorMaterial *_lineMaterial = new QSGFlatColorMaterial;

		QSGGeometryNode *_majorTickNode = new QSGGeometryNode;
		QSGGeometry *_majorTickGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                                                 0);
		QSGFlatColorMaterial *_majorTickMaterial = new QSGFlatColorMaterial;

		QSGGeometryNode *_minorTickNode = new QSGGeometryNode;
		QSGGeometry *_minorTickGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                                                 0);
		QSGFlatColorMaterial *_minorTickMaterial = new QSGFlatColorMaterial;

		void initNode(QSGGeometryNode *node,
		                  QSGGeometry *geometry,
		                  QSGFlatColorMaterial *material);
		QPointF positionDisplacement(const QRectF &canvas, const Axis *axis) const;
};


#endif // AXISNODE_H
