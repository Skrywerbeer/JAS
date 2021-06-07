#include <stdexcept>

#include "triangleoscillator.h"
#include "jass.h"

TriangleOscillator::TriangleOscillator(QObject *parent) :
    Oscillator(parent) {
	TriangleOscillator::reset();
	connect(this, &Oscillator::frequencyChanged,
	        this, &TriangleOscillator::calculateConstants);
}

TriangleOscillator::~TriangleOscillator() {
	disconnect(this, &Oscillator::frequencyChanged,
	        this, &TriangleOscillator::calculateConstants);
}

double TriangleOscillator::slewRatio() const {
	return _slewRatio;
}

void TriangleOscillator::setSlewRatio(double ratio) {
	if ((ratio < 0) || (ratio > 1))
		throw std::invalid_argument("Attempt to set slew ratio outside 0 < ratio < 1");
	if (ratio == _slewRatio)
		return;
	_slewRatio = ratio;
	emit slewRatioChanged();
	calculateConstants();
}

float TriangleOscillator::operator()() {
	_index++;
	if (_index == (_risingSampleCount + _fallingSampleCount))
		_index = 0;
	if (_index < _risingSampleCount)
		return  -_amplitude + _risingDelta*_index;
	else if (_index == _risingSampleCount )
		return _amplitude;
	else
		return _amplitude - _fallingDelta*(_index - _risingSampleCount);
}

void TriangleOscillator::reset() {
	_index = _risingSampleCount/2;
}

void TriangleOscillator::calculateConstants() {
	const int SAMPLES_PER_PERIOD = static_cast<double>(JASS::SAMPLE_RATE)/_frequency;
	_risingSampleCount = _slewRatio*SAMPLES_PER_PERIOD;
	_fallingSampleCount = (1.0 - _slewRatio)*SAMPLES_PER_PERIOD;
	_risingDelta = 2.0*_amplitude/_risingSampleCount;
	_fallingDelta = 2.0*_amplitude/_fallingSampleCount;
}
