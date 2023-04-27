#include "squarevco.h"

SquareVCO::SquareVCO(QObject *parent) :
    VCO(parent) {
	_type = Source::Type::SquareVCO;
}

double SquareVCO::dutyCycle() const {
	return _dutyCycle;
}

void SquareVCO::setDutyCycle(double duty) {
	if ((duty < 0) || (duty > 1.0))
		throw std::invalid_argument("Attempt to set duty cycle outside 0 < duty < 1");
	if (duty == _dutyCycle)
		return;
	_dutyCycle = duty;
	emit dutyCycleChanged();
}

float SquareVCO::newSample() {
	const double frequency = _frequency->operator()() + _deviation*_cv->operator()();
	const int SAMPLES_PER_PERIOD = JASS::SAMPLE_RATE/frequency;
	const int SAMPLES_ON = SAMPLES_PER_PERIOD*_dutyCycle;
	if (_index >= SAMPLES_PER_PERIOD)
		_index = 0;
	if (_index++ < SAMPLES_ON)
		return _amplitude->operator()() + _offset->operator()();
	else
		return -_amplitude->operator()() + _offset->operator()();
}

void SquareVCO::reset() {
	_index = 0;
	_cv->reset();
}
