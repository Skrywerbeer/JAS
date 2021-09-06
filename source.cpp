#include "source.h"

Source::Source(QObject *parent) :
    QObject(parent) {
	_type = Source::Type::BaseClass;
}

Source::Type Source::type() const {
	return _type;
}

float Source::operator()() {
	if (_referenceIndex == _references)
		_referenceIndex = 0;
	if (_referenceIndex == 0)
		_latestSample = newSample();
	_referenceIndex++;
	return _latestSample;
}

Source &Source::operator>>(std::vector<float> &vec) {
	for (auto &element : vec)
		element = this->operator()();
	return *this;
}

Source &Source::operator+=(std::vector<float> &vec) {
	for (auto &element : vec) {
		element += this->operator()();
	}
	return *this;
}
