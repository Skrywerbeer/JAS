#include "sinevco.h"

SineVCO::SineVCO(QObject *parent) :
    VCO(parent) {}

float SineVCO::operator()() {
	// TODO: maybe check that frequency is positive?
	const double frequency = _frequency + _deviation*_cv->operator()();
	if (_index >= JASS::SAMPLE_RATE/frequency)
		_index = 0;
	return _amplitude*sinf(JASS::TAU*
	                       frequency*
	                       static_cast<float>(_index++)*
	                       JASS::SAMPLE_PERIOD) + _offset;
}

void SineVCO::reset() {
	_index = 0;
	_cv->reset();
}
