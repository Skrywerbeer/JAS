#include "oscillator.h"
#include "jass.h"

Oscillator::Oscillator(QObject *parent) :
    Source(parent) {}

double Oscillator::frequency() const {
	return _frequency;
}

void Oscillator::setFrequency(double frequency) {
	if (frequency == _frequency)
		return;
	else if (frequency < 0)
		throw std::runtime_error("Negative frequencies are not supported.");
	else if (frequency > JASS::SAMPLE_RATE/2)
		throw std::runtime_error("Frequency does not satisfy Nyquist criterion.");
	_index = 0;
	_frequency = frequency;
	emit frequencyChanged();
}

double Oscillator::amplitude() const {
	return _amplitude;
}

void Oscillator::setAmplitude(double amplitude) {
	if (amplitude == _amplitude)
		return;
	else if (amplitude < 0 || amplitude > 1)
		throw std::runtime_error("Invalid value. 0 <= amplitude <= 1");
	_index = 0;
	_amplitude = amplitude;
	emit amplitudeChanged();
}

double Oscillator::offset() const {
	return _offset;
}

void Oscillator::setOffset(double offset) {
	if (offset == _offset)
		return;
	_offset = offset;
	emit offsetChanged();
}
