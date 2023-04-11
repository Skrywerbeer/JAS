#include "axisticks.h"

AxisTicks::AxisTicks(QObject *parent) : QObject(parent) {
	connect(this, &AxisTicks::colorChanged,
	        this, &AxisTicks::changed);
	connect(this, &AxisTicks::countChanged,
	        this, &AxisTicks::changed);
	connect(this, &AxisTicks::widthChanged,
	        this, &AxisTicks::changed);
	connect(this, &AxisTicks::lengthChanged,
	        this, &AxisTicks::changed);
}

QColor AxisTicks::color() const {
	return _color;
}

void AxisTicks::setColor(const QColor &color) {
	if (color == _color)
		return;
	_color = color;
	emit colorChanged();
}

int AxisTicks::count() const {
return _count;
}

void AxisTicks::setCount(int count) {
	if (count == _count)
		return;
	_count = count;
	emit countChanged();
}

qreal AxisTicks::width() const {
	return _width;
}

void AxisTicks::setWidth(qreal width) {
	if (width == _width)
		return;
	_width = width;
	emit widthChanged();
}

qreal AxisTicks::length() const {
	return _length;
}

void AxisTicks::setLength(qreal length) {
	if (length == _length)
		return;
	_length = length;
	emit lengthChanged();
}
