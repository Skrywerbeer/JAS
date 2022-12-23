#include <cmath>

#include "decay.h"

Decay::Decay(QObject *parent) :
    Effect(parent) {
	_type = Source::Type::Decay;
	Decay::reset();
}

int Decay::rate() const {
	return _rate;
}

void Decay::setRate(int rate) {
	if (rate == _rate)
		return;
	_rate = rate;
	reset();
	emit rateChanged();
}

float Decay::newSample() {
	const double msPerSec = 1000;
	const double rateInSec = static_cast<double>(_rate)/msPerSec;
	return _input->operator()()*std::pow(0.5, static_cast<double>(_index++)/(
	                                     rateInSec*static_cast<double>(JASS::SAMPLE_RATE)));
}

void Decay::reset() {
	if (_input != nullptr)
		_input->reset();
	_index = 0;
}
