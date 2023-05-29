#include "effect.h"

Effect::Effect(QObject *parent) :
    Source(parent) {}

Source *Effect::input() const {
	return _input;
}

void Effect::setInput(Source *input) {
	if (input == _input)
		return;
	if (_input != nullptr && !_feedbackInput)
		_input->decRefCount();
	_feedbackInput = input->isDependency(this) ? true : false;
	_input = input;
	if (!_feedbackInput)
		_input->incRefCount();
	emit inputChanged();
}

void Effect::reset() {
	if (!_feedbackInput)
		_input->reset();
	// else do nothing.
}

bool Effect::isDependency(const Source *source) const {
	if (_input == nullptr)
		return false;
	else if (_input == source)
		return true;
	else
		return _input->isDependency(source);
}
