#include "mixer.h"

Mixer::Mixer(QObject *parent) :
    Source(parent) {}

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
	_inputs.push_back(input);
}

qsizetype Mixer::inputCount() const {
	return static_cast<qsizetype>(_inputs.size());
}

Source *Mixer::input(qsizetype index) const {
	return _inputs.at(index);
}

void Mixer::clearInputs() {
	_inputs.clear();
}

void Mixer::replaceInput(qsizetype index, Source *input) {
	_inputs[index] = input;
}

void Mixer::removeLastInput() {
	_inputs.pop_back();
}

float Mixer::operator()() {
	float ret = 0;
	for (auto *input : _inputs)
		ret += input->operator()();
	return ret/_inputs.size();
}

void Mixer::reset() {
	for (auto &input : _inputs)
		input->reset();
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
