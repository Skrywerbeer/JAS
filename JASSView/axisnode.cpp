#include "axisnode.h"

AxisNode::AxisNode(const QRectF &canvas, Orientation orientation, const Axis *axis) :
    QSGNode(), _orientation(orientation) {
	initNode(_minorTickNode, _minorTickGeometry, _minorTickMaterial);
	updateMinorTickGeometry(canvas, axis);
	updateMinorTickMaterial(axis);
	appendChildNode(_minorTickNode);

	initNode(_majorTickNode, _majorTickGeometry, _majorTickMaterial);
	updateMajorTickGeometry(canvas, axis);
	updateMajorTickMaterial(axis);
	appendChildNode(_majorTickNode);

	initNode(_lineNode, _lineGeometry, _lineMaterial);
	updateGeometry(canvas, axis);
	updateMaterial(axis);
	appendChildNode(_lineNode);
}

AxisNode::~AxisNode() {
	delete _majorTickNode;
	delete _minorTickNode;
}

void AxisNode::updateGeometry(const QRectF &canvas, const Axis *axis) {
	const QPointF p0 = canvas.bottomLeft() + positionDisplacement(canvas, axis);
	QPointF p1 = positionDisplacement(canvas, axis);
	if (_orientation == Orientation::Horizontal)
		p1 += canvas.bottomRight();
	else if (_orientation == Orientation::Vertical)
		p1 += canvas.topLeft();
	else
		qFatal("AxisNode: Invalid orientation.");

	QSGGeometry::Point2D *vertices = _lineGeometry->vertexDataAsPoint2D();
	vertices[0].set(p0.x(), p0.y());
	vertices[1].set(p1.x(), p1.y());
	markDirty(QSGGeometryNode::DirtyGeometry);
}

void AxisNode::updateMajorTickGeometry(const QRectF &canvas, const Axis *axis) {
	_majorTickGeometry->allocate(2*axis->majorTicks()->count());
	_majorTickGeometry->setLineWidth(axis->majorTicks()->width());
	// Teken
	QPointF dp(0, 0);
	QPointF p0 = canvas.bottomLeft() + positionDisplacement(canvas, axis);
	QPointF p1 = canvas.bottomLeft() + positionDisplacement(canvas, axis);
	if (_orientation == Orientation::Horizontal) {
		dp.setX(canvas.width()/static_cast<double>(axis->majorTicks()->count() - 1));
		p0.setY(p0.y() - axis->majorTicks()->length()/2);
		p1.setY(p1.y() + axis->majorTicks()->length()/2);
	}
	else if (_orientation == Orientation::Vertical) {
		dp.setY(-canvas.height()/static_cast<double>(axis->majorTicks()->count() - 1));
		p0.setX(p0.x() - axis->majorTicks()->length()/2);
		p1.setX(p1.x() + axis->majorTicks()->length()/2);
	}
	else {
		qFatal("AxisNode: Invalid orientation.");
	}
	QSGGeometry::Point2D *vertices = _majorTickGeometry->vertexDataAsPoint2D();
	for (int i = 0; i < axis->majorTicks()->count(); ++i) {
		const QPointF start = p0 + i*dp;
		const QPointF end = p1 + i*dp;
		vertices[2*i].set(start.x(), start.y());
		vertices[2*i + 1].set(end.x(), end.y());
	}
	_majorTickNode->markDirty(QSGGeometryNode::DirtyGeometry);
}

void AxisNode::updateMinorTickGeometry(const QRectF &canvas, const Axis *axis) {
	if (axis->majorTicks()->count() == 0)
		return;
	const int tickCount = axis->majorTicks()->count() > 1 ?
	                          (axis->majorTicks()->count() - 1)*axis->minorTicks()->count() :
	                          axis->minorTicks()->count();

	_minorTickGeometry->allocate(2*tickCount);
	if (tickCount == 0)
		return;
	_minorTickGeometry->setLineWidth(axis->minorTicks()->width());

	// Teken
	QPointF majorTickDistance(0, 0);
	QPointF p0 = canvas.bottomLeft() + positionDisplacement(canvas, axis);
	QPointF p1 = canvas.bottomLeft() + positionDisplacement(canvas, axis);
	if (_orientation == Orientation::Horizontal) {
		majorTickDistance.setX(canvas.width()/
		                           static_cast<double>(axis->majorTicks()->count() - 1));
		p0.setY(p0.y() - axis->minorTicks()->length()/2);
		p1.setY(p1.y() + axis->minorTicks()->length()/2);
	}
	else if (_orientation == Orientation::Vertical) {
		majorTickDistance.setY(-canvas.height()/static_cast<double>(axis->majorTicks()->count() - 1));
		p0.setX(p0.x() - axis->minorTicks()->length()/2);
		p1.setX(p1.x() + axis->minorTicks()->length()/2);
	}
	else {
		qFatal("AxisNode: Invalid orientation.");
	}
	const QPointF dp = majorTickDistance/axis->minorTicks()->count();
	QSGGeometry::Point2D *vertices = _minorTickGeometry->vertexDataAsPoint2D();
	for (int i = 0; i < tickCount;++i) {
		const QPointF start = p0 + i*dp;
		const QPointF end = p1 + i*dp;
		vertices[2*i].set(start.x(), start.y());
		vertices[2*i + 1].set(end.x(), end.y());
	}
	_minorTickNode->markDirty(QSGGeometryNode::DirtyGeometry);
}

void AxisNode::updateMaterial(const Axis *axis) {
	_lineMaterial->setColor(axis->color());
	markDirty(QSGGeometryNode::DirtyMaterial);
}

void AxisNode::updateMajorTickMaterial(const Axis *axis) {
	_majorTickMaterial->setColor(axis->majorTicks()->color());
	_majorTickNode->markDirty(QSGGeometryNode::DirtyMaterial);
}

void AxisNode::updateMinorTickMaterial(const Axis *axis) {
	_minorTickMaterial->setColor(axis->minorTicks()->color());
	_minorTickNode->markDirty(QSGGeometryNode::DirtyMaterial);
}

void AxisNode::initNode(QSGGeometryNode *node,
                            QSGGeometry *geometry,
                            QSGFlatColorMaterial *material) {
	node->setGeometry(geometry);
	geometry->setDrawingMode(QSGGeometry::DrawLines);
	node->setFlag(QSGNode::OwnsGeometry);
	node->setMaterial(material);
	node->setFlag(QSGNode::OwnsMaterial);
}

QPointF AxisNode::positionDisplacement(const QRectF &canvas, const Axis *axis) const {
	if (_orientation == Orientation::Horizontal) {
		switch (axis->position()) {
		case (Axis::Position::Start):
			return QPointF(0, 0);
		case (Axis::Position::Center):
			return QPointF(0, -canvas.height()/2);
		case (Axis::Position::End):
			return QPointF(0, -canvas.height());
		}
	}
	else if (_orientation == Orientation::Vertical) {
		switch (axis->position()) {
		case (Axis::Position::Start):
			return QPointF(0, 0);
		case (Axis::Position::Center):
			return QPointF(canvas.width()/2, 0);
		case (Axis::Position::End):
			return QPointF(canvas.width(), 0);
		}
	}
	throw std::runtime_error("AxisNode: Invalid orientation.");
}
