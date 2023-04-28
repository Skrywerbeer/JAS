#ifndef PLOTNODE_H
#define PLOTNODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

#include <QPointF>

#include "interval.h"
#include "plot.h"
#include "../JASSCore/jass.h"
#include "../JASSCore/source.h"


class PlotNode : public QSGGeometryNode {
	public:
		PlotNode(qreal lineWidth=1.0, const QColor &color=QColor("black"));
		~PlotNode();

		QColor color() const;
		void setColor(const QColor &color);

		qreal lineWidth() const;
		void setLineWidth(qreal width);

		int pointCount() const;
		void setPointCount(int count);

		void movePoint(int index, const QPointF &point);
		void updateGeometry(const QRectF &canvas,
		                const Interval *xInterval,
		                const Interval *yInterval,
		                Plot *plot);
		void updateMaterial(const Plot *plot);
		QPointF mapToCanvas(const QRectF &canvas,
		                    const Interval *xInterval,
		                    const Interval *yInterval,
		                    const QPointF &p) const;

		Interval yInterval() const;
		Interval xInterval() const;
	private:
		QSGGeometry *_geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                                         0);
		QSGFlatColorMaterial *_material = new QSGFlatColorMaterial;
		QList<QPointF> _points;
};

#endif // PLOTNODE_H
