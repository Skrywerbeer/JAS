#include "source.h"

Source::Source(QObject *parent) :
    QObject(parent) {
	_type = Source::Type::BaseClass;
}

Source::Type Source::type() const {
	return _type;
}

QObject *Source::stateGroup() const {
	return _stateGroup;
}

void Source::setStateGroup(QObject *group) {
	if (group == _stateGroup)
		return;
	_stateGroup = group;
	emit stateGroupChanged();
}

float Source::operator()() {
	if (_refIndex >= _refCount)
		_refIndex = 0;
	if (_refIndex == 0)
		_latestSample = newSample();
	_refIndex++;
	return _latestSample;
	//	return newSample();
}

float Source::last() const {
	return _latestSample;
}

bool Source::isDependency(const Source *source) const {
	return false;
}

void Source::incRefCount() {
	_refCount++;
}

void Source::decRefCount() {
	if (_refCount == 0)
		throw std::runtime_error("Attempt to decrement while reference count == 0");
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
