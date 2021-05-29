#include "generator.h"

const float Generator::TAU{6.283185f};

Generator::Generator(QObject *parent) :
    QObject(parent) {}

//Generator::Generator(float frequency, float amplitude, QObject *parent) :
//    QObject(parent), _frequency(frequency), _amplitude(amplitude) {}

float Generator::frequency() const {
	return _frequency;
}

void Generator::setFrequency(float frequency) {
	if (frequency == _frequency)
		return;
	else if (frequency < 0)
		throw std::runtime_error("Negative frequencies are not supported.");
	else if (frequency > SAMPLE_RATE/2)
		throw std::runtime_error("Frequency does not satisfy Nyquist criterion.");
	_index = 0;
	_frequency = frequency;
	emit frequencyChanged();
}

float Generator::amplitude() const {
	return _amplitude;
}

void Generator::setAmplitude(float amplitude) {
	if (amplitude == _amplitude)
		return;
	else if (amplitude < 0 || amplitude > 1)
		throw std::runtime_error("Invalid value. 0 <= amplitude <= 1");
	_index = 0;
	_amplitude = amplitude;
	emit amplitudeChanged();
}

Generator &Generator::operator>>(std::vector<float> &vec) {
	for (auto &element : vec)
		element = this->operator()();
	return *this;
}

Generator &Generator::operator+=(std::vector<float> &vec) {
	for (auto &element : vec) {
		element += this->operator()();
	}
	return *this;
}
