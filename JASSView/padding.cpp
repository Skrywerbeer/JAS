#include "padding.h"

Padding::Padding(QObject *parent) : QObject(parent) {
	connect(this, &Padding::leftChanged,
	        this, &Padding::changed);
	connect(this, &Padding::rightChanged,
	        this, &Padding::changed);
	connect(this, &Padding::topChanged,
	        this, &Padding::changed);
	connect(this, &Padding::bottomChanged,
	        this, &Padding::changed);
}

qreal Padding::left() const {
	return _left;
}

void Padding::setLeft(const qreal padding) {
	if (padding == _left)
		return;
	_left = padding;
	emit leftChanged();
}

qreal Padding::right() const {
	return _right;
}

void Padding::setRight(const qreal padding) {
	if (padding == _right)
		return;
	_right = padding;
	emit rightChanged();
}

qreal Padding::top() const {
	return _top;
}

void Padding::setTop(const qreal padding) {
	if (padding == _top)
		return;
	_top = padding;
	emit topChanged();
}

qreal Padding::bottom() const {
	return _bottom;
}

void Padding::setBottom(const qreal padding) {
	if (padding == _bottom)
		return;
	_bottom = padding;
	emit bottomChanged();
}
