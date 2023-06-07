#include "pwloscillator.h"

PWLOscillator::PWLOscillator(QObject *parent) : Oscillator(parent) {

}

QQmlListProperty<PieceWisePoint> PWLOscillator::points() {
	return QQmlListProperty<PieceWisePoint>(this, this,
	                               &appendPoint,
	                               &pointCount,
	                               &point,
	                               &clearPoints,
	                               &replacePoint,
	                               &removeLastPoint);
}

void PWLOscillator::appendPoint(PieceWisePoint *point) {
	if (point->time() > 1)
		throw std::runtime_error("PWLOscillator expects time values < 1.");
	_points.push_back(point);
}

qsizetype PWLOscillator::pointCount() const {
	return _points.size();
}

PieceWisePoint *PWLOscillator::point(qsizetype index) const {
	return _points.at(index);
}

void PWLOscillator::clearPoints() {
	_points.clear();
}

void PWLOscillator::replacePoint(qsizetype index, PieceWisePoint *point) {
	_points.replace(index, point);
}

void PWLOscillator::removeLastPoint() {
	_points.removeLast();
}

float PWLOscillator::newSample() {
	if (_points.size() == 0)
		return 0;
	else if (_points.size() == 1)
		return _points.at(0)->value();
	const qreal frequency = _frequency->operator()();
	const PieceWisePoint *next = _pointIndex != _points.size() - 1 ?
	                                                _points.at(_pointIndex + 1) : _points.at(0);
	const qreal step = stepBetweenPoints(_points.at(_pointIndex), next, frequency);
	bool recalculate = false;
	if (abs(next->value() - (_lastValue)) < abs(next->value() - (_lastValue + step))) {
		_pointIndex++;
		if (_pointIndex == _points.size())
			_pointIndex = 0;
		next = _pointIndex != _points.size() - 1 ?
		                          _points.at(_pointIndex+1) : _points.at(0);
		recalculate = true;
	}
	if (!recalculate)
		_lastValue += step;
	else
		_lastValue += stepBetweenPoints(_points.at(_pointIndex), next, frequency);
	return _lastValue*_amplitude->operator()() + _offset->operator()();
}

void PWLOscillator::reset() {
	Oscillator::reset();
	if (_points.size() >= 1) {
		_lastValue = _points.at(0)->value();
		_pointIndex = 0;
	}
	else {
		_lastValue = 0;
		_pointIndex = 0;
	}
}

void PWLOscillator::appendPoint(QQmlListProperty<PieceWisePoint> *list, PieceWisePoint *point) {
	reinterpret_cast<PWLOscillator *>(list->data)->appendPoint(point);
}

qsizetype PWLOscillator::pointCount(QQmlListProperty<PieceWisePoint> *list) {
	return reinterpret_cast<PWLOscillator *>(list->data)->pointCount();
}

PieceWisePoint *PWLOscillator::point(QQmlListProperty<PieceWisePoint> *list, qsizetype index) {
	return reinterpret_cast<PWLOscillator *>(list->data)->point(index);
}

void PWLOscillator::clearPoints(QQmlListProperty<PieceWisePoint> *list) {
	reinterpret_cast<PWLOscillator *>(list->data)->clearPoints();
}

void PWLOscillator::replacePoint(QQmlListProperty<PieceWisePoint> *list, qsizetype index, PieceWisePoint *point) {
	reinterpret_cast<PWLOscillator *>(list->data)->replacePoint(index, point);
}

void PWLOscillator::removeLastPoint(QQmlListProperty<PieceWisePoint> *list) {
	reinterpret_cast<PWLOscillator *>(list->data)->removeLastPoint();
}

qreal PWLOscillator::stepBetweenPoints(const PieceWisePoint *p0,
                                 const PieceWisePoint *p1,
                                 const qreal frequency) const {
	const qreal samplesPerPeriod = static_cast<qreal>(JASS::SAMPLE_RATE)/
	                               frequency;
	qreal deltaT = p1->time() - p0->time();
	if (deltaT < 0)
		deltaT += 1.0;
	const qreal deltaV = p1->value() - p0->value();
	return deltaV/(deltaT*samplesPerPeriod);
}
