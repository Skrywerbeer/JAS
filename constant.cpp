#include <stdexcept>
#include "constant.h"

Constant::Constant(QObject *parent) :
    Source(parent) {}

double Constant::value() const {
	return _value;
}

void Constant::setValue(double value) {
	if (value == _value)
		return;
	if ((value > 1.0) || (value < -1.0))
		throw std::runtime_error("Attempt to set Constant to a value outside -1 <= value <= 1");
	_value = value;
	emit valueChanged();
}

float Constant::operator()() {
	return _value;
}

void Constant::reset() {
	// Do nothing.
}
