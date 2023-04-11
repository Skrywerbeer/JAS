#include "plotnode.h"

PlotNode::PlotNode(qreal lineWidth, const QColor &color) : QSGGeometryNode() {
	_geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
	_geometry->setLineWidth(lineWidth);
	setGeometry(_geometry);
	_material->setColor(color);
	setMaterial(_material);
}

PlotNode::~PlotNode() {
	delete _geometry;
	delete _material;
}

QColor PlotNode::color() const {
	return static_cast<QSGFlatColorMaterial *>(material())->color();
}

void PlotNode::setColor(const QColor &color) {
	static_cast<QSGFlatColorMaterial *>(material())->setColor(color);
	markDirty(QSGNode::DirtyMaterial);
}

qreal PlotNode::lineWidth() const {
	return _geometry->lineWidth();
}

void PlotNode::setLineWidth(qreal width) {
	_geometry->setLineWidth(width);
}

int PlotNode::pointCount() const {
	return _geometry->vertexCount();
}

void PlotNode::setPointCount(int count) {
	_geometry->allocate(count);
}

void PlotNode::movePoint(int index, const QPointF &point) {
	if (index >= pointCount())
		throw std::runtime_error("PlotNode: plot index out of bounds.");
	_geometry->vertexDataAsPoint2D()[index].set(point.x(), point.y());
//	markDirty(QSGGeometryNode::DirtyGeometry);
}

void PlotNode::updateGeometry(const QRectF &canvas,
                          const Interval *xInterval,
                          const Interval *yInterval,
                          Plot *plot) {
	_geometry->setLineWidth(plot->width());
	const int N = pointCount();
	const int startSampleIndex = xInterval->lowerBound()*JASS::SAMPLE_RATE;
	const int endSampleIndex = xInterval->upperBound()*JASS::SAMPLE_RATE;
	const double sampleStep = static_cast<double>(endSampleIndex - startSampleIndex)/
	                          static_cast<double>(N - 1);
	const double xStep = xInterval->width()/static_cast<double>(N - 1);
	plot->input()->reset();
	for (int pointIndex = 0, sampleIndex = 0; pointIndex < N; ++sampleIndex) {
		const int nextPlottedIndex = static_cast<double>(pointIndex)*sampleStep + static_cast<double>(startSampleIndex);
		if (sampleIndex < nextPlottedIndex) {
			plot->input()->operator ()(); // Discard the sample.
			continue;
		}
		else if (sampleIndex >= nextPlottedIndex) {
			const QPointF p(xInterval->lowerBound() + xStep*static_cast<double>(pointIndex),
			                plot->input()->operator ()());
			movePoint(pointIndex, mapToCanvas(canvas, xInterval, yInterval, p));
			pointIndex++;
		}
	}
	markDirty(QSGGeometryNode::DirtyGeometry);
}

void PlotNode::updateMaterial(const Plot *plot) {
	_material->setColor(plot->color());
	markDirty(QSGGeometryNode::DirtyMaterial);
}



QPointF PlotNode::mapToCanvas(const QRectF &canvas, 
                              const Interval *xInterval, 
                              const Interval *yInterval, 
                              const QPointF &p) const {
	const QPointF paddingDisplacement(canvas.topLeft());
	const QPointF transformed(xInterval->normailzed(p.x())*canvas.width(),
	                          (1.0 - yInterval->normailzed(p.y()))*canvas.height());
	return transformed + paddingDisplacement;
}

