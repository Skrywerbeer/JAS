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

#include "padding.h"
#include "graphnode.h"
#include "axis.h"
#include "axisnode.h"
#include "plot.h"
#include "plotnode.h"
#include "interval.h"


class LineGraph : public QQuickItem {
		Q_OBJECT
		QML_ELEMENT
		// NOTE: How does this affect reference counting?
		Q_PROPERTY(Padding *padding
		           READ padding
		           NOTIFY paddingChanged)
		Q_PROPERTY(Axis *horizontalAxis
		           READ horizontalAxis
		           NOTIFY horizontalAxisChanged)
		Q_PROPERTY(Axis *verticalAxis
		           READ verticalAxis
		           NOTIFY verticalAxisChanged)
		Q_PROPERTY(Interval *xInterval
		           READ xInterval
		           NOTIFY xIntervalChanged)
		Q_PROPERTY(Interval *yInterval
		           READ yInterval
		           NOTIFY yIntervalChanged)
		Q_PROPERTY(QQmlListProperty<Plot> plots READ plots)

		// TODO: Attached properties for vertical and horizontal axes
		// and maybe a grid.

	public:
		LineGraph(QQuickItem *parent = nullptr);
		~LineGraph();

		Padding *padding() const;
		Axis *horizontalAxis() const;
		Axis *verticalAxis() const;

		Interval *xInterval() const;
		Interval *yInterval() const;

		QQmlListProperty<Plot> plots();
		void appendPlot(const Plot *plot);
		qsizetype plotCount() const;
		Plot *plot(qsizetype index) const;
		void clearPlots();
		void replacePlot(qsizetype index, Plot *plot);
		void removeLastPlot();

		QRectF availableCanvas() const;
		qreal availableWidth() const;
		qreal availableHeight() const;

		QSGNode * updatePaintNode(QSGNode *oldNode,
		                          UpdatePaintNodeData *data) override;

	signals:
		// NOTE: Are these signals needed?
		void horizontalAxisChanged();
		void verticalAxisChanged();
		void paddingChanged();
		void xIntervalChanged();
		void yIntervalChanged();

	private:
		Padding *_padding = new Padding(this); // Does this need delete?
		Axis *_horizontalAxis = new Axis(this);
		AxisNode *_horizontalAxisNode = new AxisNode(availableCanvas(),
		                                             AxisNode::Orientation::Horizontal,
		                                             _horizontalAxis);
		Axis *_verticalAxis = new Axis(this);
		AxisNode *_verticalAxisNode = new AxisNode(availableCanvas(),
		                                           AxisNode::Orientation::Vertical,
		                                           _verticalAxis);
		QList<Plot *> _plots;
		QList<PlotNode *> _plotNodes;

		Interval *_xInterval = new Interval(this);
		Interval *_yInterval = new Interval(this);

		static void appendPlot(QQmlListProperty<Plot> *list, Plot *plot);
		static qsizetype plotCount(QQmlListProperty<Plot> *list);
		static Plot *plot(QQmlListProperty<Plot> *list, qsizetype index);
		static void clearPlots(QQmlListProperty<Plot> *list);
		static void replacePlot(QQmlListProperty<Plot> *list,
		                        qsizetype index,
		                        Plot *plot);
		static void removeLastPlot(QQmlListProperty<Plot> *list);
};

#endif
