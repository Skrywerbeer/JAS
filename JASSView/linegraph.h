#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QQuickItem>
#include <QQmlEngine>
#include <QSGNode>
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

#include "../JASSCore/jass.h"
#include "../JASSCore/source.h"


class LineGraph : public QQuickItem {
		Q_OBJECT
		QML_ELEMENT
		// NOTE: How does this affect reference counting?
		Q_PROPERTY(Source *input
		           READ input
		           WRITE setInput
		           NOTIFY inputChanged)
		Q_PROPERTY(double startTime
		           READ startTime
		           WRITE setStartTime
		           NOTIFY startTimeChanged)
		Q_PROPERTY(double endTime
		           READ endTime
		           WRITE setEndTime
		           NOTIFY endTimeChanged)
		Q_PROPERTY(QColor color
		           READ color
		           WRITE setColor
		           NOTIFY colorChanged)
		// TODO: Attached properties for vertical and horizontal axes
		// and maybe a grid.

	public:
		LineGraph(QQuickItem *parent = nullptr);

		Source *input() const;
		void setInput(const Source *input);

		double startTime() const;
		void setStartTime(const double time);

		double endTime() const;
		void setEndTime(const double time);

		QColor color() const;
		void setColor(const QColor &color);

		QSGNode * updatePaintNode(QSGNode *oldNode,
		                          UpdatePaintNodeData *data) override;

	signals:
		void inputChanged();
		void startTimeChanged();
		void endTimeChanged();
		void colorChanged();

	private:
		Source *_input = nullptr;
		double _startTime = 0;
		double _endTime = 0;
		QColor _color = Qt::black;

		void linearPlot(QSGGeometry::Point2D *vertices, int count);
};


#endif
