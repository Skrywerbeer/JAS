#include "effect.h"

Effect::Effect(QObject *parent) :
    Source(parent) {}

Source *Effect::input() const {
	return _input;
}

void Effect::setInput(Source *input) {
	if (input == _input)
		return;
	_input = input;
	emit inputChanged();
}
