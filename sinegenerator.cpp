#include "sinegenerator.h"

SineGenerator::SineGenerator(float frequency, float amplitude, uint sampleRate) :
    Generator(),
    _frequency(frequency),
    _amplitude(amplitude),
    _sampleRate(sampleRate) {}

float SineGenerator::operator()() {
	if (_index == _sampleRate/_frequency)
		_index = 0;
	return _amplitude*sinf(TAU*_frequency*static_cast<float>(_index++)/static_cast<float>(_sampleRate));
}

void SineGenerator::setSampleRate(uint value) {
	_index = 0;
	_sampleRate = value;
}

float SineGenerator::frequency() const {
	return _frequency;
}

void SineGenerator::setFrequency(float freq) {
	if (freq == _frequency)
		return;
	else if (freq < 0)
		throw std::runtime_error("Negative frequencies are not supported.");
	else if (freq > _sampleRate/2)
		throw std::runtime_error("Frequency does not satisfy Nyquist criterion.");
	_index = 0;
	_frequency = freq;
	emit frequencyChanged();
}

float SineGenerator::amplitude() const {
	return _amplitude;
}

void SineGenerator::setAmplitude(float amplitude) {
	if (amplitude == _amplitude)
		return;
	else if (amplitude < 0 || amplitude > 1)
		throw std::runtime_error("Invalid value. 0 <= amplitude <= 1");
	_index = 0;
	_amplitude = amplitude;
	emit amplitudeChanged();
}
