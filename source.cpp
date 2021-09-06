#include "source.h"

Source::Source(QObject *parent) :
    QObject(parent) {
	_type = Source::Type::BaseClass;
}

Source::Type Source::type() const {
	return _type;
}

float Source::operator()() {
	if (_refIndex == _refCount)
		_refIndex = 0;
	if (_refIndex == 0)
		_latestSample = newSample();
	_refIndex++;
	return _latestSample;
}

void Source::incRefCount() {
	_refCount++;
}

void Source::decRefCount() {
	_refCount--;
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
