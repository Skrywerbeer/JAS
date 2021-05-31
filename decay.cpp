#include <cmath>

#include "decay.h"

DecayEffect::DecayEffect(QObject *parent) :
    Source(parent) {
	DecayEffect::reset();
}

Source *DecayEffect::input() const {
	return _input;
}

void DecayEffect::setInput(const Source *input) {
	if (input == _input)
		return;
	_input = const_cast<Source *>(input);
	emit inputChanged();
}

int DecayEffect::rate() const {
	return _rate;
}

void DecayEffect::setRate(int rate) {
	if (rate == _rate)
		return;
	_rate = rate;
	reset();
	emit rateChanged();
}

float DecayEffect::operator()() {
	const double msPerSec = 1000;
	const double rateInSec = static_cast<double>(_rate)/msPerSec;
	return _input->operator()()*std::pow(0.5, static_cast<double>(_index++)/(
	                                     rateInSec*static_cast<double>(jass::SAMPLE_RATE)));
}

void DecayEffect::reset() {
	_index = 0;
}
