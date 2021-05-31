#include "sineoscillator.h"
#include "jass.h"

SineOscillator::SineOscillator(QObject *parent) :
    Oscillator(parent) {}

float SineOscillator::operator()() {
	if (_index == jass::SAMPLE_RATE/_frequency)
		_index = 0;
	return _amplitude*sinf(jass::TAU*
	                       _frequency*
	                       static_cast<float>(_index++)/static_cast<float>(jass::SAMPLE_RATE));
}

void SineOscillator::reset() {
	_index = 0;
}

