#include "exponential.h"


Exponential::Exponential(QObject *parent) : Source(parent) {

}

qreal Exponential::initial() const {
	return _initial;
}

void Exponential::setInitial(const qreal value) {
	if (value == _initial)
		return;
	_initial = value;
	emit initialChanged();
}

qreal Exponential::asymptote() const {
	return _asymptote;
}

void Exponential::setAsymptote(const qreal value) {
	if (value == _asymptote)
		return;
	_asymptote = value;
	emit asymptoteChanged();
}

qreal Exponential::timeConstant() const {
	return _timeConstant;
}

void Exponential::setTimeConstant(const qreal value) {
	if (value == _timeConstant)
		return;
	else if (value < 0)
		throw std::runtime_error("Exponential: Positive time constant required.");
	_timeConstant = value;
	emit timeConstantChanged();
}

float Exponential::newSample() {
	const double t = JASS::SAMPLE_PERIOD*static_cast<qreal>(_index++);
	return _asymptote - (_asymptote - _initial)*exp(-t/_timeConstant);
}

void Exponential::reset() {
	_index = 0;
}
