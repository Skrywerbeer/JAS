#include "trianglevco.h"

TriangleVCO::TriangleVCO(QObject *parent) :
    VCO(parent) {}

double TriangleVCO::slewRatio() const {
	return _slewRatio;
}

void TriangleVCO::setSlewRatio(double ratio) {
	if ((ratio < 0) || (ratio > 1))
		throw std::invalid_argument("Attempt to set slew ratio outside 0 < ratio < 1");
	if (ratio == _slewRatio)
		return;
	_slewRatio = ratio;
	emit slewRatioChanged();
}

float TriangleVCO::operator()() {
	const double frequency = _frequency + _deviation*_cv->operator()();
	const int SAMPLES_PER_PERIOD = static_cast<double>(JASS::SAMPLE_RATE)/frequency;
	const int risingSampleCount = _slewRatio*SAMPLES_PER_PERIOD;
	if (_index >= SAMPLES_PER_PERIOD)
		_index = 0;

	if (_index < risingSampleCount) {
		_index++;
		const double risingDelta = 2.0*_amplitude/risingSampleCount;
		return  -_amplitude + risingDelta*_index;
	}
	else if (_index == risingSampleCount ) {
		_index++;
		return _amplitude;
	}
	else {
		_index++;
		const int fallingSampleCount = (1.0 - _slewRatio)*SAMPLES_PER_PERIOD;
		const double fallingDelta = 2.0*_amplitude/fallingSampleCount;
		return _amplitude - fallingDelta*(_index - _risingSampleCount);
	}
}

void TriangleVCO::reset() {
	_index = 0;
	_cv->reset();
}
