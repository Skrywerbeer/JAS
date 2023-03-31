#include "patchboard.h"

Patchboard::Patchboard(QObject *parent) :
    Source(parent) {
	_type = Source::Type::PatchBoard;
}

QQmlListProperty<Source> Patchboard::sources() {
	return QQmlListProperty<Source>(this, this,
	                                &Patchboard::appendSource,
	                                &Patchboard::sourceCount,
	                                &Patchboard::source,
	                                &Patchboard::clearSources,
	                                &Patchboard::replaceSource,
	                                &Patchboard::removeLastSource);
}

void Patchboard::appendSource(Source *source) {
	_sources.push_back(source);
}

qsizetype Patchboard::sourceCount() const {
	return _sources.size();
}

Source *Patchboard::source(qsizetype index) const {
	return _sources.at(index);
}

void Patchboard::clearSources() {
	_sources.clear();
}

void Patchboard::replaceSource(qsizetype index, Source *source) {
	_sources[index] = source;
}

void Patchboard::removeLastSource() {
	_sources.pop_back();
}

Source *Patchboard::output() const {
	return _output;
}

void Patchboard::setOutput(Source *output) {
	if (output == _output)
		return;
	_output = output;
	emit outputChanged();
}

float Patchboard::newSample() {
	if (_output == nullptr)
		throw std::runtime_error("PatchBoard does not have an output.");
	return _output->operator()();
}

void Patchboard::reset() {
	for (auto &source : _sources)
		source->reset();
	_output->reset();
}

void Patchboard::appendSource(QQmlListProperty<Source> *list, Source *source) {
	reinterpret_cast<Patchboard *>(list->data)->appendSource(source);
}

qsizetype Patchboard::sourceCount(QQmlListProperty<Source> *list) {
	return reinterpret_cast<Patchboard *>(list->data)->sourceCount();
}

Source *Patchboard::source(QQmlListProperty<Source> *list, qsizetype index) {
	return reinterpret_cast<Patchboard *>(list->data)->source(index);
}

void Patchboard::clearSources(QQmlListProperty<Source> *list) {
	reinterpret_cast<Patchboard *>(list->data)->clearSources();
}

void Patchboard::replaceSource(QQmlListProperty<Source> *list, qsizetype index, Source *source) {
	reinterpret_cast<Patchboard *>(list->data)->replaceSource(index, source);
}

void Patchboard::removeLastSource(QQmlListProperty<Source> *list) {
	reinterpret_cast<Patchboard *>(list->data)->removeLastSource();
}
