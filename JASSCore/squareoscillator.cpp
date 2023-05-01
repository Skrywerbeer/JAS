#include <stdexcept>

#include "squareoscillator.h"

SquareOscillator::SquareOscillator(QObject *parent) :
    Oscillator(parent) {
	_type = Source::Type::SquareOscillator;
}

Source *SquareOscillator::dutyCycle() const {
	return _dutyCycle;
}

void SquareOscillator::setDutyCycle(Source *duty) {
//	if ((duty < 0) || (duty > 1.0))
//		throw std::invalid_argument("Attempt to set duty cycle outside 0 < duty < 1");
	if (duty == _dutyCycle)
		return;
	_dutyCycle = duty;
	emit dutyCycleChanged();
}

float SquareOscillator::newSample() {
	const int SAMPLES_PER_PERIOD = JASS::SAMPLE_RATE/_frequency->operator()();
	const int SAMPLES_ON = SAMPLES_PER_PERIOD*_dutyCycle->operator()();
	if (_index >= SAMPLES_PER_PERIOD)
		_index = 0;
	if (_index++ < SAMPLES_ON)
		return _amplitude->operator()() + _offset->operator()();
	else
		return -_amplitude->operator()() + _offset->operator()();
}

void SquareOscillator::reset() {
	Oscillator::reset();
	_index = 0;
}
