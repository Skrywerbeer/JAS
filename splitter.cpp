#include "splitter.h"

Splitter::Splitter(QObject *parent) :
    Effect(parent) {
	_type = Source::Type::Splitter;
}

int Splitter::outputCount() const {
	return _outputCount;
}

void Splitter::setOutputCount(int count) {
	if (count == _outputCount)
		return;
	_outputCount = count;
	emit outputCountChanged();
}

float Splitter::operator()() {
	if (_outputIndex == _outputCount)
		_outputIndex = 0;
	if (_outputIndex == 0)
		_latestValue = _input->operator()();
	_outputIndex++;
	return _latestValue;
}

void Splitter::reset() {
	_outputIndex = 0;
	_input->reset();
}
