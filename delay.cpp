#include "delay.h"

Delay::Delay(QObject *parent) :
    Effect(parent), _buffer(_delay*JASS::SAMPLES_PER_US) {
	_type = Source::Type::Delay;
}

int Delay::delay() const {
	return _delay;
}

void Delay::setDelay(int delay) {
	if (delay == _delay)
		return;
	_delay = delay;
	emit delayChanged();
}

float Delay::operator()() {
	return _buffer << _input->operator()();
}

void Delay::reset() {
	_buffer.zero();
	_input->reset();
}
