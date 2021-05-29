#include "sineoscillator.h"
#include "jass.h"

SineGenerator::SineGenerator(QObject *parent) :
    Oscillator(parent) {}

float SineGenerator::operator()() {
	if (_index == jass::SAMPLE_RATE/_frequency)
		_index = 0;
	return _amplitude*sinf(jass::TAU*
	                       _frequency*
	                       static_cast<float>(_index++)/static_cast<float>(jass::SAMPLE_RATE));
}

void SineGenerator::reset() {
	_index = 0;
}

