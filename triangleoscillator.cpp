#include <stdexcept>

#include "triangleoscillator.h"
#include "jass.h"

TriangleOscillator::TriangleOscillator(QObject *parent) :
    Oscillator(parent) {}

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
}

float TriangleOscillator::operator()() {
	const int SAMPLES_PER_PERIOD = static_cast<double>(JASS::SAMPLE_RATE)/_frequency;
	// _index == 0 when counting up, _index == 1 when counting down.
	if (_lastValue >= _amplitude)
		_index = 1;
	else if (_lastValue <= -_amplitude)
		_index = 0;
	if (!_index) {
		const int risingSampleCount = _slewRatio*SAMPLES_PER_PERIOD;
		if (risingSampleCount == 0) {
			_lastValue = _amplitude;
		}
		else {
			const double risingDelta = 2.0*_amplitude/risingSampleCount;
			_lastValue += risingDelta;
		}
	}
	else {
		const int fallingSampleCount = (1.0 - _slewRatio)*SAMPLES_PER_PERIOD;
		if (fallingSampleCount == 0) {
			_lastValue = -_amplitude;
		}
		else {
			const double fallingDelta = 2.0*_amplitude/fallingSampleCount;
			_lastValue -= fallingDelta;
		}
	}
	return _lastValue;
}

void TriangleOscillator::reset() {
	_index = 0;
	_lastValue = 0;
}

