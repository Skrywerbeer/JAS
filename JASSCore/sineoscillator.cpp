#include "sineoscillator.h"
#include "jass.h"

SineOscillator::SineOscillator(QObject *parent) :
    Oscillator(parent) {
	_type = Source::Type::SineOscillator;
}

float SineOscillator::newSample() {
	if (_index == JASS::SAMPLE_RATE/_frequency->operator()())
		_index = 0;
	return _amplitude->operator()()*sinf(JASS::TAU*
	                       _frequency->operator()()*
	                       static_cast<float>(_index++)*
	                       JASS::SAMPLE_PERIOD) + _offset->operator()();
}

void SineOscillator::reset() {
	_index = 0;
}

