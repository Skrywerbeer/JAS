#include "oscillator.h"
#include "jass.h"

Oscillator::Oscillator(QObject *parent) :
    Source(parent) {}

Source *Oscillator::frequency() const {
	return _frequency;
}

void Oscillator::setFrequency(Source *frequency) {
	if (frequency == _frequency)
		return;
//	else if (frequency-> < 0)
//		throw std::runtime_error("Negative frequencies are not supported.");
//	else if (frequency->value() > JASS::SAMPLE_RATE/2)
//		throw std::runtime_error("Frequency does not satisfy Nyquist criterion.");
//	_index = 0;
	_frequency = frequency;
	emit frequencyChanged();
}

Source *Oscillator::amplitude() const {
	return _amplitude;
}

void Oscillator::setAmplitude(Source *amplitude) {
	if (amplitude == _amplitude)
		return;
//	_index = 0;
	_amplitude = amplitude;
	emit amplitudeChanged();
}

Source *Oscillator::offset() const {
	return _offset;
}

void Oscillator::setOffset(Source *offset) {
	if (offset == _offset)
		return;
	_offset = offset;
	emit offsetChanged();
}

void Oscillator::reset() {
	_frequency->reset();
	_amplitude->reset();
	_offset->reset();
}
