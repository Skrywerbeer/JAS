#include "mixer.h"

Mixer::Mixer(QObject *parent) :
    Source(parent) {
	_type = Source::Type::Mixer;
}

QQmlListProperty<Source> Mixer::inputs() {
	return QQmlListProperty<Source>(this, this,
	                                &appendInput,
	                                &inputCount,
	                                &input,
	                                &clearInputs,
	                                &replaceInput,
	                                &removeLastInput);
}

void Mixer::appendInput(Source *input) {
	const bool usesFeedback = input->isDependency(this);
	if (!usesFeedback)
		input->incRefCount();
	_inputs.push_back(MixerInput(input, usesFeedback));
}

qsizetype Mixer::inputCount() const {
	return static_cast<qsizetype>(_inputs.size());
}

Source *Mixer::input(qsizetype index) const {
	return _inputs.at(index).source;
}

void Mixer::clearInputs() {
	for (auto &input : _inputs)
		if (!input.feedbackInput)
			input.source->decRefCount();
	_inputs.clear();
}

void Mixer::replaceInput(qsizetype index, Source *input) {
	if (_inputs.at(index).feedbackInput)
		_inputs[index].source->decRefCount();
	const bool usesFeedback = input->isDependency(this);
	if (!usesFeedback)
		input->incRefCount();
	_inputs[index].source = input;
	_inputs[index].feedbackInput = usesFeedback;
}

void Mixer::removeLastInput() {
	MixerInput input = _inputs.back();
	if (!input.feedbackInput)
		input.source->decRefCount();
	_inputs.pop_back();
}

float Mixer::newSample() {
	float ret = 0;
	for (auto input : _inputs) {
		if (!input.feedbackInput)
			ret += input.source->operator()();
		else
			ret += input.source->last();
	}

	return ret/_inputs.size();
}

void Mixer::reset() {
	for (auto &input : _inputs)
		if (!input.feedbackInput)
			input.source->reset();
}

bool Mixer::isDependency(const Source *source) const {
	for (const auto input : _inputs)
		if ((input.source == source) || (input.source->isDependency(source)))
			return true;
	return false;
}

void Mixer::appendInput(QQmlListProperty<Source> *list, Source *input) {
	reinterpret_cast<Mixer *>(list->data)->appendInput(input);
}

qsizetype Mixer::inputCount(QQmlListProperty<Source> *list) {
	return reinterpret_cast<Mixer *>(list->data)->inputCount();
}

Source *Mixer::input(QQmlListProperty<Source> *list, qsizetype index) {
	return reinterpret_cast<Mixer *>(list->data)->input(index);
}

void Mixer::clearInputs(QQmlListProperty<Source> *list) {
	reinterpret_cast<Mixer *>(list->data)->clearInputs();
}

void Mixer::replaceInput(QQmlListProperty<Source> *list, qsizetype index, Source *input) {
	reinterpret_cast<Mixer *>(list->data)->replaceInput(index, input);
}

void Mixer::removeLastInput(QQmlListProperty<Source> *list) {
	reinterpret_cast<Mixer *>(list->data)->removeLastInput();
}
