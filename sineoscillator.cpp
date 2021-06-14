#include "sineoscillator.h"
#include "jass.h"

SineOscillator::SineOscillator(QObject *parent) :
    Oscillator(parent) {
	_type = Source::Type::SineOscillator;
}

float SineOscillator::operator()() {
	if (_index == JASS::SAMPLE_RATE/_frequency)
		_index = 0;
	return _amplitude*sinf(JASS::TAU*
	                       _frequency*
	                       static_cast<float>(_index++)*
	                       JASS::SAMPLE_PERIOD) + _offset;
}

void SineOscillator::reset() {
	_index = 0;
}

