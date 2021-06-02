#include <stdexcept>

#include "whitenoise.h"

WhiteNoise::WhiteNoise(QObject *parent) :
    Source(parent) {
	std::random_device r;
	_twister.seed(r());
}

double WhiteNoise::amplitude() const {
	return _amplitude;
}

void WhiteNoise::setAmplitude(double amplitude) {
	if ((amplitude < 0) || (amplitude > 1))
		throw std::invalid_argument("Attempting to set amplitude outside range 0 < amplitude < 1");
	if (amplitude == _amplitude)
		return;
	_amplitude = amplitude;
	emit amplitudeChanged();
}

float WhiteNoise::operator()() {
	const float noise = 2.0*(static_cast<float>(_twister())/_twister.max() - 0.5);
	return _amplitude*noise;
}

void WhiteNoise::reset() {
	// Do nothing.
}
