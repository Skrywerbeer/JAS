#include "axis.h"


Axis::Axis(QObject *parent) : QObject(parent) {}

bool Axis::visible() const {
	return _visible;
}

void Axis::setVisible(bool value) {
	if (value == _visible)
		return;
	_visible = value;
	emit visibleChanged();
}

QColor Axis::color() const {
	return _color;
}

void Axis::setColor(const QColor &color) {
	if (color == _color)
		return;
	_color = color;
	emit colorChanged();
}

Axis::Position Axis::position() const {
	return _position;
}

void Axis::setPosition(const Position pos) {
	if (pos == _position)
		return;
	_position = pos;
	emit positionChanged();
}

AxisTicks *Axis::majorTicks() const {
	return _majorTicks;
}

AxisTicks *Axis::minorTicks() const {
	return _minorTicks;
}
