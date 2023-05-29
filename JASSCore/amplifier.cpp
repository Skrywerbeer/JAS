#include "amplifier.h"


Amplifier::Amplifier(QObject *parent) : Effect(parent) {}

Source *Amplifier::gain() const {
	return _gain;
}

void Amplifier::setGain(Source *gain) {
	if (gain == _gain)
		return;
	_gain = gain;
	emit gainChanged();
}

float Amplifier::newSample() {
	return _gain->operator()()*_input->operator()();
}

void Amplifier::reset() {
	Effect::reset();
	_gain->reset();
}

bool Amplifier::isDependency(const Source *source) const {
	return Effect::isDependency(source) || _gain->isDependency(source);
}
