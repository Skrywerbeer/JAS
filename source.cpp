#include "source.h"

Source::Source(QObject *parent) : QObject(parent) {}

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
