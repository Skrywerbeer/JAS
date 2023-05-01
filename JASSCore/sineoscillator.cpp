#include "sineoscillator.h"
#include "jass.h"

SineOscillator::SineOscillator(QObject *parent) :
    Oscillator(parent) {
	_type = Source::Type::SineOscillator;
}

float SineOscillator::newSample() {
	const double frequency = _frequency->operator()();
//	if (_index == JASS::SAMPLE_RATE/frequency)
//		_index = 0;
	return _amplitude->operator()()*sinf(JASS::TAU*
	                       frequency*
	                       static_cast<float>(_index++)*
	                       JASS::SAMPLE_PERIOD) + _offset->operator()();
}

void SineOscillator::reset() {
	Oscillator::reset();
	_index = 0;
}

