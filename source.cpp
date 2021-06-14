#include "source.h"

Source::Source(QObject *parent) :
    QObject(parent) {
	_type = Source::Type::BaseClass;
}

Source::Type Source::type() const {
	return _type;
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
