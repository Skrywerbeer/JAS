#include "piecewisefunction.h"


PieceWiseFunction::PieceWiseFunction(QObject *parent) : Source (parent) {

}

QQmlListProperty<PieceWisePoint> PieceWiseFunction::points() {
	return QQmlListProperty<PieceWisePoint>(this, this,
	                               &appendPoint,
	                               &pointCount,
	                               &point,
	                               &clearPoints,
	                               &replacePoint,
	                               &removeLastPoint);
}

void PieceWiseFunction::appendPoint(PieceWisePoint *value) {
	_points.push_back(value);
}

qsizetype PieceWiseFunction::pointCount() const {
	return _points.size();
}

PieceWisePoint *PieceWiseFunction::point(qsizetype index) const {
	return _points.at(index);
}

void PieceWiseFunction::clearPoints() {
	_points.clear();
}

void PieceWiseFunction::replacePoint(qsizetype index, PieceWisePoint *point) {
	_points.replace(index, point);
}

void PieceWiseFunction::removeLastPoint() {
	_points.removeLast();
}

float PieceWiseFunction::newSample() {
	if (_points.size() == 0)
		return 0;
	else if (_points.size() == 1)
		return _points.at(0)->value();

	int nextPointStartIndex = _points.at(_pointIndex)->time()*JASS::SAMPLE_RATE;
	if (_sampleIndex == nextPointStartIndex) {
		if (_pointIndex == _points.size() - 1) {
			return _points.at(_pointIndex)->value();
		}
		else {
			_pointIndex++;
			nextPointStartIndex = _points.at(_pointIndex)->time()*JASS::SAMPLE_RATE;
		}
	}
	const int currentPointStartIndex = _points.at(_pointIndex - 1)->time()*JASS::SAMPLE_RATE;
	const int sectionIndexWidth = nextPointStartIndex - currentPointStartIndex;
	const qreal sectionValueDelta = _points.at(_pointIndex)->value() -
	                                _points.at(_pointIndex - 1)->value();
	const int index = _sampleIndex++ - currentPointStartIndex;
	return _points.at(_pointIndex - 1)->value() +
	        (sectionValueDelta/static_cast<qreal>(sectionIndexWidth))*index;
}

void PieceWiseFunction::reset() {
	_sampleIndex = 0;
	_pointIndex = 1;
}

void PieceWiseFunction::appendPoint(QQmlListProperty<PieceWisePoint> *list, PieceWisePoint *point) {
	reinterpret_cast<PieceWiseFunction *>(list->data)->appendPoint(point);
}

qsizetype PieceWiseFunction::pointCount(QQmlListProperty<PieceWisePoint> *list) {
	return reinterpret_cast<PieceWiseFunction *>(list->data)->pointCount();
}

PieceWisePoint *PieceWiseFunction::point(QQmlListProperty<PieceWisePoint> *list, qsizetype index) {
	return reinterpret_cast<PieceWiseFunction *>(list->data)->point(index);
}

void PieceWiseFunction::clearPoints(QQmlListProperty<PieceWisePoint> *list) {
	reinterpret_cast<PieceWiseFunction *>(list->data)->clearPoints();
}

void PieceWiseFunction::replacePoint(QQmlListProperty<PieceWisePoint> *list, qsizetype index, PieceWisePoint *point) {
	reinterpret_cast<PieceWiseFunction *>(list->data)->replacePoint(index, point);
}

void PieceWiseFunction::removeLastPoint(QQmlListProperty<PieceWisePoint> *list) {
	reinterpret_cast<PieceWiseFunction *>(list->data)->removeLastPoint();
}

