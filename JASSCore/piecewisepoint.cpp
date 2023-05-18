#include "piecewisepoint.h"

PieceWisePoint::PieceWisePoint(QObject *parent) : QObject(parent) {

}

qreal PieceWisePoint::value() const {
	return _value;
}

void PieceWisePoint::setValue(const qreal value) {
	if (value == _value)
		return;
	_value = value;
	emit valueChanged();
}

qreal PieceWisePoint::time() const {
	return _time;
}

void PieceWisePoint::setTime(const qreal time) {
	if (time == _time)
		return;
	_time = time;
	emit timeChanged();
}
