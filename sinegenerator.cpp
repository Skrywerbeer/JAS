#include "sinegenerator.h"

SineGenerator::SineGenerator(QObject *parent) :
    Generator(parent) {}

//SineGenerator::SineGenerator(float frequency, float amplitude, QObject *parent) :
//    Generator(frequency, amplitude, parent) {}

float SineGenerator::operator()() {
	if (_index == SAMPLE_RATE/_frequency)
		_index = 0;
	return _amplitude*sinf(TAU*_frequency*static_cast<float>(_index++)/static_cast<float>(SAMPLE_RATE));
}

void SineGenerator::reset() {
	_index = 0;
}

