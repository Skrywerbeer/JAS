#include "interval.h"

Interval::Interval(QObject *parent) : QObject(parent) {
	connect(this, &Interval::lowerBoundChanged,
	        this, &Interval::changed);
	connect(this, &Interval::upperBoundChanged,
	        this, &Interval::changed);
}

qreal Interval::lowerBound() const {
	return _lowerBound;
}

void Interval::setLowerBound(qreal value) {
	if (value == _lowerBound)
		return;

	_lowerBound = value;
	if (value > _upperBound)
		throw std::runtime_error("Interval: Lower bound required to be <= upper.");
	emit lowerBoundChanged();
}

qreal Interval::upperBound() const {
	return _upperBound;
}

void Interval::setUpperBound(qreal value) {
	if (value == _upperBound)
		return;
	if (value < _lowerBound)
		throw std::runtime_error("Interval: Upper bound required to be >= lower.");
	_upperBound = value;
	emit upperBoundChanged();
}

qreal Interval::normailzed(const qreal x) const {
	return (x - _lowerBound)/(_upperBound - _lowerBound);
}

qreal Interval::width() const {
	return _upperBound - _lowerBound;
}

void Interval::swapBounds() {
	const qreal temp = _lowerBound;
	_lowerBound = _upperBound;
	_upperBound = temp;
}
