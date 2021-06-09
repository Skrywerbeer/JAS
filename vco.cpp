#include "vco.h"

VCO::VCO(QObject *parent) :
    Oscillator(parent) {}

Source *VCO::cv() const {
	return _cv;
}

void VCO::setCV(Source *cv) {
	if (cv == _cv)
		return;
	_cv = cv;
	emit cvChanged();
}

double VCO::deviation() const {
	return _deviation;
}

void VCO::setDeviation(double deviation) {
	if (deviation == _deviation)
		return;
	_deviation = deviation;
	emit deviationChanged();
}
