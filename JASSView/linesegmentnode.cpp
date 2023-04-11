#include "linesegmentnode.h"

LineSegmentNode::LineSegmentNode(const QColor &color) : QSGGeometryNode() {
	setGeometry(_geometry);
	_material->setColor(color);
	setMaterial(_material);
}

LineSegmentNode::~LineSegmentNode() {
	delete _geometry;
	delete _material;
}

QPointF LineSegmentNode::p1() const {
	const auto vertices = _geometry->vertexDataAsPoint2D();
	return QPointF(vertices[0].x, vertices[0].y);
}

void LineSegmentNode::setP1(const QPointF &point) {
	_geometry->vertexDataAsPoint2D()[0].set(point.x(), point.y());
	markDirty(QSGGeometryNode::DirtyGeometry);
}

QPointF LineSegmentNode::p2() const {
	const auto vertices = _geometry->vertexDataAsPoint2D();
	return QPointF(vertices[1].x, vertices[1].y);
}

void LineSegmentNode::setP2(const QPointF &point) {
	_geometry->vertexDataAsPoint2D()[1].set(point.x(), point.y());
	markDirty(QSGGeometryNode::DirtyGeometry);
}

QColor LineSegmentNode::color() const {
	return _material->color();
}

void LineSegmentNode::setColor(const QColor &color) {
	_material->setColor(color);
	markDirty(QSGGeometryNode::DirtyMaterial);
}

