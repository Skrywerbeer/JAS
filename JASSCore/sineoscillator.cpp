#include "sineoscillator.h"
#include "jass.h"

SineOscillator::SineOscillator(QObject *parent) :
    Oscillator(parent) {
	_type = Source::Type::SineOscillator;
}

float SineOscillator::newSample() {
	const double frequency = _frequency->operator()();
//	if (_index == JASS::SAMPLE_RATE/frequency)
//		_index = 0;
//	double time = JASS::TAU*
//	              frequency*
//	              static_cast<qreal>(_index++)*
//	              JASS::SAMPLE_PERIOD;
//	while (time > JASS::TAU)
//		time -= JASS::TAU;
//	return _amplitude->operator()()*sin(time) + _offset->operator()();
	using namespace std::complex_literals;
	const std::complex step = std::exp(2.0*std::acos(-1)*frequency*JASS::SAMPLE_PERIOD*1i);
	_last *= step;
	return _last.imag()*_amplitude->operator ()() + _offset->operator ()();
}

void SineOscillator::reset() {
	Oscillator::reset();
	_index = 0;
	_last = 1;
}

