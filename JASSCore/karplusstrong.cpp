#include "karplusstrong.h"

KarplusStrongOscillator::KarplusStrongOscillator(QObject *parent) :
    Oscillator(parent) {
	std::random_device r;
	_twister.seed(r());
	reset();
}

float KarplusStrongOscillator::newSample() {
	if (!_plucked) {
		// NOTE: check for latency problems.
		reset();
		_plucked = true;
	}
	if (_index == _buffer.size())
		_index = 0;
	const qreal y1 = _buffer.at(_index);
	const std::size_t previousIndex = _index == 0 ?
	                                      _buffer.size() - 1 : _index - 1;
	const qreal y0 = _buffer.at(previousIndex);
	_buffer[_index] = 0.5*(y1 + y0);
	return _buffer.at(_index++);
}

void KarplusStrongOscillator::reset() {
	_buffer.resize(JASS::SAMPLE_RATE/_frequency->operator()());
	for (auto &sample : _buffer)
		sample = _amplitude->operator()()*
		         2.0*(static_cast<float>(_twister())/_twister.max() - 0.5) +
		         _offset->operator()();
	_index = 0;
	_plucked = false;
}
