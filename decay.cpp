#include <cmath>

#include "decay.h"

Decay::Decay(QObject *parent) :
    Source(parent) {
	Decay::reset();
}

Source *Decay::input() const {
	return _input;
}

void Decay::setInput(const Source *input) {
	if (input == _input)
		return;
	_input = const_cast<Source *>(input);
	emit inputChanged();
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

float Decay::operator()() {
	const double msPerSec = 1000;
	const double rateInSec = static_cast<double>(_rate)/msPerSec;
	return _input->operator()()*std::pow(0.5, static_cast<double>(_index++)/(
	                                     rateInSec*static_cast<double>(jass::SAMPLE_RATE)));
}

void Decay::reset() {
	_index = 0;
}
