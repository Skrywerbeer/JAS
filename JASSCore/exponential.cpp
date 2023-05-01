#include "exponential.h"


Exponential::Exponential(QObject *parent) : Source(parent) {

}

Source *Exponential::initial() const {
	return _initial;
}

void Exponential::setInitial(Source *value) {
	if (value == _initial)
		return;
	_initial = value;
	emit initialChanged();
}

Source *Exponential::asymptote() const {
	return _asymptote;
}

void Exponential::setAsymptote(Source *value) {
	if (value == _asymptote)
		return;
	_asymptote = value;
	emit asymptoteChanged();
}

Source *Exponential::timeConstant() const {
	return _timeConstant;
}

void Exponential::setTimeConstant(Source *value) {
	if (value == _timeConstant)
		return;
//	else if (value < 0)
//		throw std::runtime_error("Exponential: Positive time constant required.");
	_timeConstant = value;
	emit timeConstantChanged();
}

float Exponential::newSample() {
	const double asymptote = _asymptote->operator()();
	const double initial = _initial->operator()();
	const double timeConstant = _timeConstant->operator()();
	if (timeConstant < 0)
		throw std::runtime_error("Exponential: Positive time constant required.");
	const double t = JASS::SAMPLE_PERIOD*static_cast<qreal>(_index++);
	return asymptote - (asymptote - initial)*exp(-t/timeConstant);
}

void Exponential::reset() {
	_index = 0;
}
